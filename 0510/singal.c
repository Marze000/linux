/*信号的处理
 *  sighandler_t signal(int signum, sighandler_t handler);
 *   signum: 信号编号    handler:信号处理方式
 *                            SIG_DFL: 默认处理方式
 *                            SIG_IGN: 忽略处理方式
 *   typedef void(*sighandler_t)(int); 用户自定义信号回调函数类型
 * */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigcb(int signo)
{
  printf("recv a signal:%d\n",signo);
}

int main()
{

  signal(SIGINT,sigcb);
  signal(SIGQUIT,sigcb);
  while(1)
  {
    printf("hello maze!!\n");
    sleep(1);
  }

  return 0;
}
