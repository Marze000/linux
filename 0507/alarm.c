#include <stdio.h>
#include <unistd.h>

int main()
{
  int count = 15;
  alarm(1);
  for(;count>0;++count)
  {
    printf("%d\n",count);
  }

  return 0;
}
