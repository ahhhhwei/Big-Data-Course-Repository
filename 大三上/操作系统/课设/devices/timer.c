#include "devices/timer.h"
#include <debug.h>
#include <inttypes.h>
#include <round.h>
#include <stdio.h>
#include "devices/pit.h"
#include "threads/interrupt.h"
#include "threads/synch.h"
#include "threads/thread.h"

#if TIMER_FREQ < 19
#error 8254 timer requires TIMER_FREQ >= 19
#endif
#if TIMER_FREQ > 1000
#error TIMER_FREQ <= 1000 recommended
#endif

static int64_t ticks;

static unsigned loops_per_tick;

static intr_handler_func timer_interrupt;
static bool too_many_loops(unsigned loops);
static void busy_wait(int64_t loops);
static void real_time_sleep(int64_t num, int32_t denom);
static void real_time_delay(int64_t num, int32_t denom);

void timer_init(void) {
  pit_configure_channel(0, 2, TIMER_FREQ);
  intr_register_ext(0x20, timer_interrupt, "8254 Timer");
}

void timer_calibrate(void) {
  unsigned high_bit, test_bit;

  ASSERT(intr_get_level() == INTR_ON);
  printf("Calibrating timer...  ");

  loops_per_tick = 1u << 10;
  while (!too_many_loops(loops_per_tick << 1)) {
    loops_per_tick <<= 1;
    ASSERT(loops_per_tick != 0);
  }

  high_bit = loops_per_tick;
  for (test_bit = high_bit >> 1; test_bit != high_bit >> 10; test_bit >>= 1)
    if (!too_many_loops(loops_per_tick | test_bit))
      loops_per_tick |= test_bit;

  printf("%'" PRIu64 " loops/s.\n", (uint64_t)loops_per_tick * TIMER_FREQ);
}

int64_t timer_ticks(void) {
  enum intr_level old_level = intr_disable();
  int64_t t = ticks;
  intr_set_level(old_level);
  return t;
}

int64_t timer_elapsed(int64_t then) { return timer_ticks() - then; }

bool is_hier;  

void timer_sleep(int64_t ticks)
{
  is_hier = false;

  if (ticks <= 0)
  {
    return;
  }
  else if(ticks >= 200000)   
  {
    is_hier = true;
    ticks = 20000;   
  }
  ASSERT(intr_get_level() == INTR_ON);
  enum intr_level old_level = intr_disable();
  struct thread* cur_thread = thread_current();
  cur_thread->ticks_blocked = ticks;
  thread_block();
  intr_set_level(old_level);
}

void timer_msleep(int64_t ms) { real_time_sleep(ms, 1000); }

void timer_usleep(int64_t us) { real_time_sleep(us, 1000 * 1000); }

void timer_nsleep(int64_t ns) { real_time_sleep(ns, 1000 * 1000 * 1000); }

void timer_mdelay(int64_t ms) { real_time_delay(ms, 1000); }

void timer_udelay(int64_t us) { real_time_delay(us, 1000 * 1000); }

void timer_ndelay(int64_t ns) { real_time_delay(ns, 1000 * 1000 * 1000); }

void timer_print_stats(void) { printf("Timer: %" PRId64 " ticks\n", timer_ticks()); }

static void timer_interrupt(struct intr_frame* args UNUSED) {
  ticks++;

  thread_tick();

  thread_foreach (blocked_thread_check, NULL);
  
  if (active_sched_policy==SCHED_FAIR)
  {   
    mlfqs_inc_recent_cpu();
    if (ticks % TIMER_FREQ == 0)
      mlfqs_update_load_avg_and_recent_cpu();
    else if (ticks % 4 == 0)
      mlfqs_update_priority(thread_current());
  }
}

static bool too_many_loops(unsigned loops) {
  int64_t begin = ticks;
  while (ticks == begin)
    barrier();

  begin = ticks;
  busy_wait(loops);

  barrier();
  return begin != ticks;
}

static void NO_INLINE busy_wait(int64_t loops) {
  while (loops-- > 0)
    barrier();
}

static void real_time_sleep(int64_t num, int32_t denom) {
  int64_t ticks = num * TIMER_FREQ / denom;

  ASSERT(intr_get_level() == INTR_ON);
  if (ticks > 0) 
  {
    timer_sleep(ticks);
  } else 
  {
    real_time_delay(num, denom);
  }
}

static void real_time_delay(int64_t num, int32_t denom) {
  ASSERT(denom % 1000 == 0);
  busy_wait(loops_per_tick * num / 1000 * TIMER_FREQ / (denom / 1000));
}

