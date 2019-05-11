/*************************************************************
 * 线程等待
 * 首先思考为什么需要线程等待？
 * (1)由于已经退出的线程资源没有完全释放，所以会形成“僵尸线程”
 * (2)创建新的线程不会复用刚才退出的线程空间
 * 系统提供一个函数 int pthread_join(pthread_t thread,**value_ptr);
 *   参数  thread    线程id                  value_ptr  指向一个指针
 *   返回值 成功返回0  失败返回错误码
 *
 *调用该函数的线程将挂起等待,直到id为thread的线程终止。
 *thread线程以不同的方法终止,通过pthread_join得到的终止状态是不同的
 *  1. 如果thread线程通过return返回,value_ptr 所指向的单元里存放的是thread线程函数的返回值。
 *  2. 如果thread线程被别的线程调用pthread_cancel 异常终掉,
 *      value_ ptr所指向的单元里存放的是常数PTHREAD_CANCELED。
 *  3. 如果thread线程是自己调用pthread_exit终止的,
 *     value_ptr所指向的单元存放的是传给pthread_exit的参数。
 *  4. 如果对thread线程的终止状态不感兴趣,可以传NULL给value_ ptr参数。*
 *
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread1(void *arg)
{
  printf("thread 1 returning ... \n");
  int *p = (int*)malloc(sizeof(int));
  *p = 1;
  return (void*)p;
}

void *thread2(void *arg)
{
  printf("thread 2 exiting ...\n");
  int *p = (int*)malloc(sizeof(int));
  *p = 2;
  pthread_exit((void*)p);
}

void* thread3(void *arg)
{
  while (1)
  { 
     printf("thread 3 is running ...\n");
     sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  void *ret;

  // thread 1 return
  pthread_create(&tid, NULL, thread1, NULL);
  pthread_join(tid, &ret);
  //如果 thread 线程通过return返回
  //value_ptr 所指向的单元里存放的是thread 线程函数的返回值。
  printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
  free(ret);

   // thread 2 exit
  pthread_create(&tid, NULL, thread2, NULL);
  pthread_join(tid, &ret);
   //如果thread线程是自己调用pthread_exit终止的,
   // value_ptr所指向的单元存放的是传给pthread_exit的参数。
  printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
  free(ret);

   // thread 3 cancel by other
  pthread_create(&tid, NULL, thread3, NULL);
  sleep(3);
  pthread_cancel(tid);
   // 如果thread线程被别的线程调用pthread_cancel 异常终掉,
   //    value_ ptr所指向的单元里存放的是常数PTHREAD_CANCELED。
  pthread_join(tid, &ret);

  if (ret == PTHREAD_CANCELED)
  {  
     printf("thread return, thread id %X, return code:PTHREAD_CANCELED\n", tid);
  }
  else
  {
     printf("thread return, thread id %X, return code:NULL\n", tid);
  }

  return 0;
}

