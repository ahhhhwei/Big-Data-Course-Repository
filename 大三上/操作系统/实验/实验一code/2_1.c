#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID 是 %ld\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret != 0) {
        printf("线程创建失败\n");
        exit(EXIT_FAILURE);
    }

    // 等待线程执行完毕
    pthread_join(tid, NULL);

    return 0;
}