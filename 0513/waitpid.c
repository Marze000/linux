#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t ret1 = fork();
  if(ret1 == 0)
  {
    //child
    sleep(1);
    printf("i am child 1 :%d\n",getpid());
    exit(0);
  }
  
  pid_t ret2 = fork();
  if(ret2 == 0)
  {
    //child 2
    sleep(3);
    printf("i am child 2 :%d\n",getpid());
    exit(0);
  }

  int res;
  int count = 0;
  while(1)
  {
    res = waitpid(ret2,NULL,WNOHANG);
    printf("waitpid res:%d\n",res);
    sleep(1);
    if(res>0)
    {
      break;
    }
  }

  printf("count :%d\n",count);

  res = wait(NULL);
  printf("wait res:%d\n",res);

  while(1)
  {
    sleep(1);
  }

  return 0;
}
