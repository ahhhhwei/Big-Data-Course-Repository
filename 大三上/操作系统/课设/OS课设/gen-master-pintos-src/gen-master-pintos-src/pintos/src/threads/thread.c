#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <random.h>
#include <stdio.h>
#include <string.h>
#include "threads/flags.h"
#include "threads/interrupt.h"
#include "threads/intr-stubs.h"
#include "threads/palloc.h"
#include "threads/switch.h"
#include "threads/synch.h"
#include "threads/vaddr.h"
#ifdef USERPROG
#include "userprog/process.h"
#endif


fixed_point_t load_avg;
extern bool is_hier;
bool thread_mlfqs;
bool schedule_started;

#define THREAD_MAGIC 0xcd6abf4b

static struct list fifo_ready_list;

static struct list all_list;

static struct thread* idle_thread;

static struct thread* initial_thread;

static struct lock tid_lock;

struct kernel_thread_frame {
  void* eip;             /* Return address. */
  thread_func* function; /* Function to call. */
  void* aux;             /* Auxiliary data for function. */
};

static long long idle_ticks;   /* # of timer ticks spent idle. */
static long long kernel_ticks; /* # of timer ticks in kernel threads. */
static long long user_ticks;   /* # of timer ticks in user programs. */

#define TIME_SLICE 4          /* # of timer ticks to give each thread. */
static unsigned thread_ticks; /* # of timer ticks since last yield. */

static void init_thread(struct thread*, const char* name, int priority);
static bool is_thread(struct thread*) UNUSED;
static void* alloc_frame(struct thread*, size_t size);
static void schedule(void);
static void thread_enqueue(struct thread* t);
static tid_t allocate_tid(void);
void thread_switch_tail(struct thread* prev);

static void kernel_thread(thread_func*, void* aux);
static void idle(void* aux UNUSED);
static struct thread* running_thread(void);

static struct thread* next_thread_to_run(void);
static struct thread* thread_schedule_fifo(void);
static struct thread* thread_schedule_prio(void);
static struct thread* thread_schedule_fair(void);
static struct thread* thread_schedule_mlfqs(void);
static struct thread* thread_schedule_reserved(void);

enum sched_policy active_sched_policy;

typedef struct thread* scheduler_func(void);

scheduler_func* scheduler_jump_table[8] = {thread_schedule_fifo,     thread_schedule_prio,
                                           thread_schedule_fair,     thread_schedule_mlfqs,
                                           thread_schedule_reserved, thread_schedule_reserved,
                                           thread_schedule_reserved, thread_schedule_reserved};

void thread_init(void) {
  ASSERT(intr_get_level() == INTR_OFF);

  lock_init(&tid_lock);
  list_init(&fifo_ready_list);
  list_init(&all_list);

  initial_thread = running_thread();
  init_thread(initial_thread, "main", PRI_DEFAULT);
  initial_thread->status = THREAD_RUNNING;
  initial_thread->tid = allocate_tid();
}

void thread_start(void) {
  struct semaphore idle_started;
  load_avg=FP_CONST(0);
  schedule_started=true;
  sema_init(&idle_started, 0);
  thread_create("idle", PRI_MIN, idle, &idle_started);

  intr_enable();

  sema_down(&idle_started);
}

void thread_tick(void) {
  struct thread* t = thread_current();

  if (t == idle_thread)
    idle_ticks++;
  else if (t->pcb != NULL)
    user_ticks++;
  else
    kernel_ticks++;

  if (++thread_ticks >= TIME_SLICE)
    intr_yield_on_return();
}

void thread_print_stats(void) {
  printf("Thread: %lld idle ticks, %lld kernel ticks, %lld user ticks\n", idle_ticks, kernel_ticks,
         user_ticks);
}

tid_t thread_create(const char* name, int priority, thread_func* function, void* aux) {
  struct thread* t;
  struct kernel_thread_frame* kf;
  struct switch_entry_frame* ef;
  struct switch_threads_frame* sf;
  tid_t tid;

  ASSERT(function != NULL);

  t = palloc_get_page(PAL_ZERO);
  if (t == NULL)
    return TID_ERROR;

  init_thread(t, name, priority);
  tid = t->tid = allocate_tid();
  t->ticks_blocked = 0;

  kf = alloc_frame(t, sizeof *kf);
  kf->eip = NULL;
  kf->function = function;
  kf->aux = aux;

  ef = alloc_frame(t, sizeof *ef);
  ef->eip = (void (*)(void))kernel_thread;

  sf = alloc_frame(t, sizeof *sf);
  sf->eip = switch_entry;
  sf->ebp = 0;

  thread_unblock(t);

  if (thread_current ()->priority < priority)  {
     thread_yield ();
 }

  return tid;
}

void thread_block(void) {
  ASSERT(!intr_context());
  ASSERT(intr_get_level() == INTR_OFF);

  thread_current()->status = THREAD_BLOCKED;
  schedule();
}

static void thread_enqueue(struct thread* t) {
  ASSERT(intr_get_level() == INTR_OFF);
  ASSERT(is_thread(t));

  if (active_sched_policy == SCHED_FIFO)
    list_push_back(&fifo_ready_list, &t->elem);
  else
    PANIC("Unimplemented scheduling policy value: %d", active_sched_policy);
}


void
thread_unblock (struct thread *t)
{
  enum intr_level old_level;

  ASSERT (is_thread (t));

  old_level = intr_disable ();
  ASSERT (t->status == THREAD_BLOCKED);
  list_insert_ordered(&fifo_ready_list, &t->elem, (list_less_func *) &thread_cmp_priority, NULL);
  t->status = THREAD_READY;
  intr_set_level (old_level);
}

const char* thread_name(void) { return thread_current()->name; }

struct thread* thread_current(void) {
  struct thread* t = running_thread();

  ASSERT(is_thread(t));
  ASSERT(t->status == THREAD_RUNNING);

  return t;
}

tid_t thread_tid(void) { return thread_current()->tid; }

void thread_exit(void) {
  ASSERT(!intr_context());

  intr_disable();
  list_remove(&thread_current()->allelem);
  thread_current()->status = THREAD_DYING;
  schedule();
  NOT_REACHED();
}

void thread_yield(void) {
  if(!schedule_started)
        return;
  struct thread* cur = thread_current();
  enum intr_level old_level;

  ASSERT(!intr_context());

  old_level = intr_disable();
  if (cur != idle_thread)
    list_insert_ordered (&fifo_ready_list, &cur->elem, (list_less_func *) &thread_cmp_priority, NULL);
  cur->status = THREAD_READY;
  schedule();
  intr_set_level(old_level);
}

void thread_foreach(thread_action_func* func, void* aux) {
  struct list_elem* e;

  ASSERT(intr_get_level() == INTR_OFF);

  for (e = list_begin(&all_list); e != list_end(&all_list); e = list_next(e)) {
    struct thread* t = list_entry(e, struct thread, allelem);
    func(t, aux);
  }
}

void
thread_set_priority (int new_priority)
{
  if (active_sched_policy==SCHED_FAIR)
    return;

  enum intr_level old_level = intr_disable();

  struct thread *current_thread = thread_current();
  int old_priority = current_thread->priority;
  current_thread->base_priority = new_priority;

  if (list_empty (&current_thread->locks) || new_priority > old_priority)
  {
    current_thread->priority = new_priority;
    thread_yield();
  }

  intr_set_level(old_level);
}

int thread_get_priority(void) { return thread_current()->priority; }

void thread_set_nice(int nice UNUSED) { 
  thread_current()->nice = nice;
  mlfqs_update_priority(thread_current());
  thread_yield();
}

int thread_get_nice(void) {
  return thread_current()->nice;
}

int thread_get_load_avg(void) {
  return FP_ROUND (FP_MULT_MIX (load_avg, 100));
}

int thread_get_recent_cpu(void) {
  return FP_ROUND (FP_MULT_MIX (thread_current()->recent_cpu, 100));
}


static void idle(void* idle_started_ UNUSED) {
  struct semaphore* idle_started = idle_started_;
  idle_thread = thread_current();
  sema_up(idle_started);

  for (;;) {
    intr_disable();
    thread_block();

    asm volatile("sti; hlt" : : : "memory");
  }
}

/* Function used as the basis for a kernel thread. */
static void kernel_thread(thread_func* function, void* aux) {
  ASSERT(function != NULL);

  intr_enable(); /* The scheduler runs with interrupts off. */
  function(aux); /* Execute the thread function. */
  thread_exit(); /* If function() returns, kill the thread. */
}

struct thread* running_thread(void) {
  uint32_t* esp;

  asm("mov %%esp, %0" : "=g"(esp));
  return pg_round_down(esp);
}

static bool is_thread(struct thread* t) { return t != NULL && t->magic == THREAD_MAGIC; }

static void init_thread(struct thread* t, const char* name, int priority) {
  enum intr_level old_level;

  ASSERT(t != NULL);
  ASSERT(PRI_MIN <= priority && priority <= PRI_MAX);
  ASSERT(name != NULL);

  memset(t, 0, sizeof *t);
  t->status = THREAD_BLOCKED;
  strlcpy(t->name, name, sizeof t->name);
  t->stack = (uint8_t*)t + PGSIZE;
  t->priority = priority;
  t->pcb = NULL;
  t->magic = THREAD_MAGIC;

  t->base_priority = priority;
  list_init(&t->locks);
  t->lock_waiting = NULL;
  t->ticks=0;

  if(is_hier){
  t->nice = 0;
}
else {
  if(priority==56)
  {
    t->nice=0;
  }
  else if(priority==48)
  {
    t->nice=1;
  }
  else if(priority==40)
  {
    t->nice=2;
  }
  else if(priority==32)
  {
    t->nice=3;
  }
  else if(priority==24)
  {
    t->nice=4;
  }
  else if(priority==16)
  {
    t->nice=5;
  }
  else if(priority==8)
  {
    t->nice=6;
  }
  else if(priority==0)
  {
    t->nice=7;
  }
  }
  t->recent_cpu =FP_CONST (0);

  old_level = intr_disable();
  list_insert_ordered (&all_list, &t->allelem, (list_less_func *) &thread_cmp_priority, NULL);
  intr_set_level(old_level);
}

static void* alloc_frame(struct thread* t, size_t size) {
  ASSERT(is_thread(t));
  ASSERT(size % sizeof(uint32_t) == 0);

  t->stack -= size;
  return t->stack;
}

static struct thread* thread_schedule_fifo(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread;

}

static struct thread* thread_schedule_prio(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread;
}

static struct thread* thread_schedule_fair(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread;  
}

static struct thread* thread_schedule_mlfqs(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread;
}

static struct thread* thread_schedule_reserved(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread; 
}


static struct thread* next_thread_to_run(void) {
  if (!list_empty(&fifo_ready_list))
    return list_entry(list_pop_front(&fifo_ready_list), struct thread, elem);
  else
    return idle_thread;
}


void thread_switch_tail(struct thread* prev) {
  struct thread* cur = running_thread();

  ASSERT(intr_get_level() == INTR_OFF);

  /* Mark us as running. */
  cur->status = THREAD_RUNNING;

  /* Start new time slice. */
  thread_ticks = 0;

#ifdef USERPROG
  /* Activate the new address space. */
  process_activate();
#endif

  if (prev != NULL && prev->status == THREAD_DYING && prev != initial_thread) {
    ASSERT(prev != cur);
    palloc_free_page(prev);
  }
}

static void schedule(void) {
  struct thread* cur = running_thread();
  struct thread* next = next_thread_to_run();
  struct thread* prev = NULL;

  ASSERT(intr_get_level() == INTR_OFF);
  ASSERT(cur->status != THREAD_RUNNING);
  ASSERT(is_thread(next));

  if (cur != next)
    prev = switch_threads(cur, next);
  thread_switch_tail(prev);
}

static tid_t allocate_tid(void) {
  static tid_t next_tid = 1;
  tid_t tid;

  lock_acquire(&tid_lock);
  tid = next_tid++;
  lock_release(&tid_lock);

  return tid;
}

void blocked_thread_check(struct thread *t, void *aux UNUSED)
{
  if (t->status == THREAD_BLOCKED && t->ticks_blocked > 0)
  {
      t->ticks_blocked--;
      if (t->ticks_blocked == 0)
      {
          thread_unblock(t);
      }
  }
}

bool thread_cmp_priority(const struct list_elem *a, const struct list_elem *b, void *aux UNUSED)
{
  return list_entry(a, struct thread, elem)->priority > list_entry(b, struct thread, elem)->priority;  // 比较两个线程的优先级，返回true如果a的优先级高于b的优先级
}

void thread_donate_priority(struct thread *thread)
{
   enum intr_level old = intr_disable ();
   thread_update_priority (thread);
 
   if (thread->status == THREAD_READY)
   {
     list_remove (&thread->elem);
     list_insert_ordered (&fifo_ready_list, &thread->elem, thread_cmp_priority, NULL);
   }
   intr_set_level (old);
}

void thread_hold_the_lock(struct lock *lock)
{
  enum intr_level old_level = intr_disable ();
  list_insert_ordered (&thread_current ()->locks, &lock->elem, lock_cmp_priority, NULL);

  if (lock->max_priority > thread_current ()->priority)
  {
    thread_current ()->priority = lock->max_priority;
    thread_yield ();
  }
  intr_set_level (old_level);
}

void mlfqs_update_load_avg_and_recent_cpu()
{
  ASSERT(active_sched_policy==SCHED_FAIR);
  ASSERT(intr_context());

  size_t cnt = list_size(&fifo_ready_list);
  if (thread_current() != idle_thread)
  {
    ++cnt;
  }
  load_avg = FP_ADD (FP_DIV_MIX (FP_MULT_MIX (load_avg, 59), 60), FP_DIV_MIX(FP_CONST(cnt), 60));

  struct thread *thread;
  struct list_elem *e;
  for (e = list_begin(&all_list); e != list_end(&all_list); e = list_next(e))
  {
    thread = list_entry(e, struct thread, allelem);
    if (thread != idle_thread)
    {

      thread->recent_cpu =FP_ADD_MIX (FP_MULT (FP_DIV (FP_MULT_2_F(load_avg, 1), FP_ADD_MIX (FP_MULT_2_F(load_avg, 1), 1)), thread->recent_cpu), 0);

      mlfqs_update_priority(thread);
    }
  }
}

void thread_remove_lock(struct lock *lock)
{
  enum intr_level old = intr_disable ();
  list_remove (&lock->elem);
  thread_update_priority (thread_current ());
  intr_set_level (old);
}

void thread_update_priority(struct thread *t)
{
  enum intr_level old = intr_disable ();
  int max_priority = t->base_priority;  
  int lock_priority;  

  if (!list_empty (&t->locks))
  {
    // 对锁列表进行排序，根据锁的最大优先级进行排序
    list_sort (&t->locks, lock_cmp_priority, NULL);
    lock_priority = list_entry (list_front (&t->locks), struct lock, elem)->max_priority;
    if (lock_priority > max_priority)
      max_priority = lock_priority;
  }

  t->priority = max_priority;
  intr_set_level(old);
}

bool lock_cmp_priority(const struct list_elem *a, const struct list_elem *b, void *aux UNUSED)
{
  return list_entry (a, struct lock, elem)->max_priority > list_entry (b, struct lock, elem)->max_priority;
}

void mlfqs_inc_recent_cpu()
{
  ASSERT(active_sched_policy==SCHED_FAIR);
  ASSERT(intr_context());

  struct thread *cur = thread_current();
  if (cur == idle_thread)
    return;
  cur->recent_cpu = FP_ADD_MIX(cur->recent_cpu, 1);
}

void mlfqs_update_priority(struct thread *t)
{
  ASSERT(active_sched_policy==SCHED_FAIR);
  
  if (t == idle_thread)
    return;
  if(is_hier)  
  {
    t->priority = FP_INT_PART (FP_SUB_MIX (FP_SUB (FP_CONST (PRI_MAX), (FP_DIV_MIX (t->recent_cpu, 4))),t->nice)); 
  }
  else
  {
    t->priority = FP_INT_PART (FP_SUB_MIX (FP_SUB (FP_CONST (PRI_MAX), FP_DIV_MIX(t->recent_cpu, 4)),0));
  }

  if (t->priority < PRI_MIN)
    t->priority = PRI_MIN;
  else if (t->priority > PRI_MAX)
    t->priority = PRI_MAX;
}

void thread_fair_update_ticks(void)
{
  struct thread* current_thread=thread_current();
  if(current_thread==idle_thread)return;
  current_thread->ticks=current_thread->ticks+1;
  if(current_thread->ticks>=current_thread->priority){  
    current_thread->ticks=0;
    if(!intr_context())thread_yield();
    else intr_yield_on_return();
  }
}
uint32_t thread_stack_ofs = offsetof(struct thread, stack);





