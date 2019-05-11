#include <stdio.h>
#include <signal.h> 


int a = 1;

void sigcb(int no)
{
  a = 0;
  printf("a:%d\n",a);
}

int main()
{
  signal(SIGINT,sigcb);
  while(a)
  {
    ;
  }
  printf("normal exit!\n");
  return 0;
}
