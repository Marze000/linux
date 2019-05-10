/*信号的处理
 * int sigaction(int signum,  const struct sigaction *act,  struct sigaction *oldact);
 *              signum: 信号编号  act：信号新的处理动作   oldact：保存信号原有的处理动作
 *   
 *
 * */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>

void sigcb(int signo)
{
  printf("signal:%d\n",signo);
}

int main()
{

  struct sigaction act,old;
  act.sa_handler = sigcb;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(SIGINT,&act,&old);

  while(1)
  {
    printf("hello maze!!\n");
    sleep(1);
  }

  return 0;
}
