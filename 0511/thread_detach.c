/*****************************************************************8
 *分离线程
 *
 * 分离一个线程，将线程的属性从 joinable 设置为 detach 属性；
 * 属于detach属性的线程退出后不需要被等待，自动回收资源；
 * 分离一个线程的前提就是-----用户对线程的退出返回值不关心
 * pthread_detach 线程分离可以是任意线程在任意时刻进行分离---
 * 对于一个线程来说分离和等待是互相冲突的，一个线程不能既是分离又是joinable的
 *
 **************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *thread_run( void * arg  )
{
  pthread_detach(pthread_self());
  printf("%s\n", (char*)arg);
  return NULL;
}

int main( void  )
{
  pthread_t tid;
  if (pthread_create(&tid, NULL, thread_run, "thread1 run...") != 0)
  {
     printf("create thread error\n");
     return 1;
  }

  int ret = 0;
  sleep(1);//很重要，要让线程先分离，再等待
  if (pthread_join(tid, NULL ) == 0  )
  {
    printf("pthread wait success\n");
    ret = 0;
  }

  else 
  {
    printf("pthread wait failed\n");
    ret = 1;
  }

  return ret;
}
