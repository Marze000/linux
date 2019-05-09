#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handel(int signal)
{
  printf("catch a signal :%d\n",signal);
}

int main()
{
  signal(SIGSEGV,handel);
  sleep(1);
  int *p = NULL;
  *p = 100;

  while(1);

  return 0;
}
