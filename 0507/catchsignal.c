#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handel(int signal)
{
  printf("catch a signal :%d\n",signal);
}

int main()
{
  sleep(1);
  signal(2,handel);

  while(1);

  return 0;
}
