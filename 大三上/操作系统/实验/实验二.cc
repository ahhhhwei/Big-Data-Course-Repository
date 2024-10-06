#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

int readerCount = 0;
int writerCount = 0;
sem_t rcsignal;
sem_t filesrc; 
sem_t read_s;

sem_t RCSIGNAL;
sem_t writeCountSignal;
sem_t WRT;
sem_t READ_S;

class thread_info 
{
public:
    int thread_id;
    char thread_type;
    double thread_delay;
    double thread_lastTime;
};

// 读者优先
void *rp_threadReader(void *p) 
{
    int num_thread = ((thread_info *)p)->thread_id;
    double delaytime = ((thread_info *)p)->thread_delay;
    double duration = ((thread_info *)p)->thread_lastTime;

    usleep(delaytime * 1000000);
    cout << "读者线程" << num_thread << " 发送了一个读请求" << endl;
    sem_wait(&rcsignal); // P
    if (readerCount == 0) sem_wait(&filesrc);
    readerCount++;
    sem_post(&rcsignal); // V
    cout << "读者线程" << num_thread << " 开始读文件" << endl;
    usleep(duration * 1000000);
    cout << "读者线程" << num_thread << " 读完了文件" << endl;
    sem_wait(&rcsignal); // P
    readerCount--;
    if (readerCount == 0) sem_post(&filesrc);
    sem_post(&rcsignal); // V
    pthread_exit(NULL);
}

void *rp_threadWriter(void *p) 
{
    int num_thread = ((thread_info *)p)->thread_id;
    double delaytime = ((thread_info *)p)->thread_delay;
    double duration = ((thread_info *)p)->thread_lastTime;

    usleep(delaytime * 1000000);
    cout << "写者线程" << num_thread << " 发送了一个写请求" << endl;
    sem_wait(&filesrc);
    cout << "写者线程" << num_thread << " 开始写文件 " << endl;
    usleep(duration * 1000000);
    cout << "写者线程" << num_thread << " 写完了文件 " << endl;
    sem_post(&filesrc);
    pthread_exit(NULL);
}

// 读者优先
void ReaderPriority() 
{
    int n_thread, i;
    cout << "读者优先：" << endl;
    cout << "输入计划处理的线程数：";
    cin >> n_thread;
    sem_init(&rcsignal, 0, 1); 
    sem_init(&filesrc, 0, 1); 
    pthread_t threads[n_thread];
    thread_info thread_info[n_thread];

    cout << "分别输入线程序号、线程类别、线程开始时间、线程读写操作时间" << endl;
    for (i = 0; i < n_thread; i++) 
    {
        cin >> thread_info[i].thread_id >> thread_info[i].thread_type >> thread_info[i].thread_delay >> thread_info[i].thread_lastTime;
    }

    for (i = 0; i < n_thread; i++) 
    {
        if (thread_info[i].thread_type == 'r' || thread_info[i].thread_type == 'R') {
            pthread_create(&threads[i], NULL, rp_threadReader, &thread_info[i]);
        } 
        else 
        {
            pthread_create(&threads[i], NULL, rp_threadWriter, &thread_info[i]);
        }
    }

    for (i = 0; i < n_thread; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    cout << "所有读者写者均已完成。" << endl;
}

// 写者优先
void *wp_threadReader(void *p) 
{
    unsigned int delaytime;
    unsigned int duration;
    int num_thread;
    
    num_thread = ((thread_info*)(p))->thread_id;
    delaytime = (unsigned int)(((thread_info*)(p))->thread_delay * 1000000);
    duration = (unsigned int)(((thread_info*)(p))->thread_lastTime * 1000000);
    usleep(delaytime); 
    cout << "读者线程 " << num_thread << " 发送了一个读请求" << endl;
    sem_wait(&READ_S);
    sem_wait(&RCSIGNAL);
    if (readerCount == 0)
        sem_wait(&WRT);
    readerCount++;
    sem_post(&RCSIGNAL);
    sem_post(&READ_S);

    cout << "读者线程 " << num_thread << " 开始读文件" << endl;
    usleep(duration);
    cout << "读者线程 " << num_thread << " 读完了文件" << endl;
    sem_wait(&RCSIGNAL);
    readerCount--;
    if (readerCount == 0)
        sem_post(&WRT);
    sem_post(&RCSIGNAL);
    pthread_exit(NULL);
}

void *wp_threadWriter(void *p) 
{
    unsigned int delaytime;
    unsigned int duration;
    int num_thread;
    
    num_thread = ((thread_info*)(p))->thread_id;
    delaytime = (unsigned int)(((thread_info*)(p))->thread_delay * 1000000);
    duration = (unsigned int)(((thread_info*)(p))->thread_lastTime * 1000000);
    usleep(delaytime); 
    cout << "写者线程 " << num_thread << " 发送了一个写请求" << endl;
    sem_wait(&writeCountSignal);
    if (writerCount == 0)
        sem_wait(&READ_S);
    writerCount++;
    sem_post(&writeCountSignal);
    sem_wait(&WRT);

    cout << "写者线程 " << num_thread << " 开始写文件" << endl;
    usleep(duration);
    cout << "写者线程 " << num_thread << " 写完了文件" << endl;
    sem_post(&WRT);
    sem_wait(&writeCountSignal);
    writerCount--;
    if (writerCount == 0)
        sem_post(&READ_S);
    sem_post(&writeCountSignal);
    pthread_exit(NULL);
}

void WriterPriority() 
{
    int n_thread = 0;
    pthread_t h_Thread[64];
    thread_info thread_info[64];
    int readerCount = 0;
    int writerCount = 0;
    
    sem_init(&RCSIGNAL, 0, 1);
    sem_init(&writeCountSignal, 0, 1);
    sem_init(&WRT, 0, 1);
    sem_init(&READ_S, 0, 1);
    cout << "写者优先" << endl;
    cout << "输入计划处理的线程数：";
    int j;
    cin >> j;
    cout << "分别输入线程序号、线程类别、线程开始时间、线程读写操作时间" << endl;
    while (n_thread < j) 
    {
        int id1;
        char type1;
        double delay1, lastTime1;
        cin >> id1 >> type1 >> delay1 >> lastTime1;
        thread_info[n_thread].thread_id = id1;
        thread_info[n_thread].thread_type = type1;
        thread_info[n_thread].thread_delay = delay1;
        thread_info[n_thread].thread_lastTime = lastTime1;
        n_thread++;
    }
    
    for (int i = 0; i < n_thread; i++) 
    {
        if (thread_info[i].thread_type == 'R' || thread_info[i].thread_type == 'r') 
        {
            pthread_create(&h_Thread[i], NULL, wp_threadReader, &thread_info[i]);
        } 
        else 
        {
            pthread_create(&h_Thread[i], NULL, wp_threadWriter, &thread_info[i]);
        }
    }

    for (int i = 0; i < n_thread; i++) 
    {
        pthread_join(h_Thread[i], NULL);
    }
    cout << "所有读者写者均已完成。" << endl;
    sem_destroy(&RCSIGNAL);
    sem_destroy(&writeCountSignal);
    sem_destroy(&WRT);
    sem_destroy(&READ_S);
}

int main() {
    char choice;
    while (true) {
        cout << "请选择：" << endl;
        cout << "1. 读者优先" << endl;
        cout << "2. 写者优先" << endl;
        cout << "3. 退出" << endl;
        cout << endl;

        cin >> choice;
        if (choice == '1') {
             
            ReaderPriority();
            cout << "\n按任意键以继续" << endl;
            cin.get();
        } 
        else if (choice == '2') 
        {
            WriterPriority();
            cout << "\n按任意键以继续" << endl;
            cin.get(); 
        } 
        else 
        {
            return 0;
        }
    }
}
