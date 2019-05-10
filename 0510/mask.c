/**********************************************************************
 * >信号的阻塞--  阻止信号被处理
 *  先将所有的信号阻塞，
 *  按回车程序继续运行，
 *  将所有信号解除阻塞
 *  int sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
 *      how  对信号阻塞集合要进行的动作
 *           SIG_BLOCK     block = block | set 将set中的信号添加到阻塞集合
 *           SIG_UNBLOCK   block = block & (~set) 对set中的信号解除阻塞
 *           SIG_SETMASK   block = set  将阻塞集合设置为set的信号
 *      set
 *      oldset  用于保存原来的信号集合
 *****************************************************************************/
#include <stdio.h>
#include <signal.h>

int main()
{
  sigset_t set,oldset;

  sigemptyset(&set); // 清空set信号集合
  
  //将所有信号添加到set集合中
  // int sigfillset(sigset_t *set);
  sigfillset(&set);

  //将signum 信号添加到set集合中
  // int sigaddset(sigset_t *set,int signum);

  //将signum 信号从set集合中移除
  // int sigdelset(sigset_t *set, int signum);

  sigprocmask(SIG_BLOCK,&set,&oldset);

  printf("press enter to continue");
  getchar();
 
  sigprocmask(SIG_UNBLOCK,&set,NULL);

  return 0;
}
