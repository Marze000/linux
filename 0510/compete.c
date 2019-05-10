#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int a = 0;
int b = 0;

int test()
{
  ++a;
  sleep(5);
  ++b;
  return a+b;
}

void sigcb()
{
  printf("signal----%d\n",test());
}

int main()
{
  signal(SIGINT,sigcb);
  printf("%d\n",test());
  

  return 0;
}
