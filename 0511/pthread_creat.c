/*线程的创建
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)
                                                                    (void*), void *arg);
  (1) thread  返回线程ID
  (2) attr    设置线程的属性，attr为NULL表示使用默认属性
  (3) start_routine 是个函数地址，线程启动后要执行的函数
  (4) arg     传给线程启动函数的参数
  返回值：成功返回0；失败返回错误码
*****************************************************8*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *rout(void* arg)
{
  while(1)
  {
    printf("i am a thread \n");
    sleep(1);
  }
}

int main()
{
  pthread_t tid;

  int ret = pthread_create(&tid,NULL,rout,NULL);
  if(ret != 0)
  {
    fprintf(stderr,"pthread_creat:%s\n",strerror(ret));
    exit(EXIT_FAILURE);
  }

  while(1)
  {
    printf("i an main thread ----\n");
    sleep(1);
  }
  return 0;
}

