#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
  printf("rec a signal:%d\n",signo);
}

int main()
{
  //signal(SIGINT,sigcb);
  //signal(SIGQUIT,sigcb);

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

  //alarm(0);//取消上一定时器
  //insighandler_t signal(int signum , sighandler_t handler);
  //signum:信号编号    handler :信号处理方式
  //                          (1)SIG_DFL  默认处理方式
  //                          (2)SIG_IGN  忽略处理方式
  //typedef void (*sighandler_t)(int):用户自定义信号回调函数类型
  

  //这条语句的意思就是，如果程序运行起来
  //输入信号编号的时候，操作系统忽略此信号
  signal(SIGINT,SIG_IGN);
  
  //sigaction(int signum,const struct sigaction* act,struct sigaction ) ;
  
  while(1)
  {
    printf("hehe\n");
    sleep(1);
  }
  return 0;
}

