#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
  int count = 0;
  //上面这条语句不能写在创建子进程之后，否则父进程执行的时候会被初始化0；
  //int i = 0;
  pid_t pid = vfork();
  //pid_t pid = fork();
  int i = 0;
  //下面这段代码会被父子进程各执行一次，由子进程拷贝父进程的代码段
  
  //父子进程的数据段互不影响；所以下面打印出来的count都是1；
  //如果把上面的fork换成vfork会变成2吗？不会。
  //如果仅仅把fork换成vfork不会改变count，虽然vfork是数据段共享的，但是vfork的一个特点就是
  //子进程会先于父进程运行，在子进程调用exit 或exec之后父进程才会运行，否则会导致死锁
  //所以在子进程中加入exit，然后父进程才会运行，这时候count会变为2；
  if(pid<0)
  {
    perror("fork errno");
    return -1;
  }
  else if(pid ==0)
  {
   
    for(;i<5;++i) 
    {
      printf("count = %d   ",++count);
      printf("i am a child pid:%d ,return: %d\n",getpid(),pid);
      
    }    
    _exit(0);
  }
  else
  {
   
    for(;i<5;++i) 
    {
       printf("count = %d  ",++count);
       printf("i am a parent pid:%d,return: %d\n",getpid(),pid);
    }    
  }

  return 0;
}
