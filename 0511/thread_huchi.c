//临界资源：多线程执行流共享的资源就叫做临界资源
//如果多个线程共享临界资源就会出现问题
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int gal_v = 10;

void* thread1(void* arg)
{
  gal_v = 20;
  printf("gal_v = %d\n",gal_v);
}

void* thread2(void* arg)
{
  sleep(1);
  printf("gal_v = %d\n",gal_v);
}

int main()
{

  pthread_t pid1,pid2;

  int tet = pthread_create(&pid1,NULL,thread1,NULL);
  if(tet==0){
      printf("make sucess\n");
  }
  int ret = pthread_create(&pid2,NULL,thread2,NULL);
  if(ret == 0)
  {
    printf("make sucess\n");
  }

  pthread_join(pid1,NULL);
  pthread_join(pid2,NULL);
  return 0;
}
