#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t id=fork();
    if(id==0)
    {
      // child
        printf("我是子进程, pid:%d\n", getpid());
        sleep(1);
    }
    else 
    {
      // parent
      printf("我是父进程，pid:%d,\n",getpid());
    }
    return 0;
}