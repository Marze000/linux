#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  //int kill(pid_t pid,int sig)
  //给进程pid 发送sig信号
  //kill(getpid(),SIGKILL);
  //kill(getpid(),SIGQUIT);
  //raise(SIGQUIT);
  
  //void abort(void) ;
  //abort();
  //给调用进程发送SIGABRT信号
  
  //unsigned int alarm(unsigned int seconds) 
  //seconds 秒之后，给调用进程发送SIGALRM 信号
  //alarm(3);

  alarm(0);//取消上一定时器
  while(1)
  {
    printf("hehe\n");
    sleep(1);
  }
  return 0;
}
