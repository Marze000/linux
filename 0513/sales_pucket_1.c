
//操作共享变量的售票系统
//该代码没有互斥行为
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int ticket = 100;

void *route(void *arg)
{
  char *id = (char*)arg;
  while(1)
  {
    if (ticket > 0)
    {
      usleep(1000);
      printf("%s sells ticket:%d\n", id, ticket);
      ticket--;
    }
    else{break;}
  }
}

int main( void  )
{
  pthread_t t1, t2, t3, t4;

  pthread_create(&t1, NULL, route, "thread 1");
  pthread_create(&t2, NULL, route, "thread 2");
  pthread_create(&t3, NULL, route, "thread 3");
  pthread_create(&t4, NULL, route, "thread 4");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  return 0;
}
//通过执行代码会发现有一定的错误，是因为当一个线程在执行临界区的时候
//会有其他线程进入，这样就导致了在打印的时候会有相同的重复结果picket

