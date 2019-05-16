/************************************************************************
 * 操作共享变量的售票系统
 *
 *(1)代码必须要有互斥行为：当代码进入临界区执行时，不允许其他线程进入该临界区。
 *(2)如果多个线程同时要求执行临界区的代码，并且临界区没有线程在执行，
 *   那么只能允许一个线程进入该临界区。
 *(3)如果线程不在临界区中执行，那么该线程不能阻止其他线程进入临界区


(i)   初始化互斥量--静态分配  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER
      动态分配 int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                          const pthread_mutexattr_t*restrict attr);
      参数： mutex：要初始化的互斥量     attr：NULL
    
(ii)  销毁互斥量 int pthread_mutex_destroy(pthread_mutex_t *mutex)；    

(iii) 互斥量的加锁 int pthread_mutex_lock(pthread_mutex_t *mutex);
      互斥量的解锁 int pthread_mutex_unlock(pthread_mutex_t *mutex);
                   返回值:成功返回0,失败返回错误号

                  
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int ticket = 100;
pthread_mutex_t mutex;//定义互斥量

//临界区
void *route(void *arg)
{
  char *id = (char*)arg;
  while(1)
  {
    //这行会有其他线程，但是由于上锁，进不去
    
    //加锁
    pthread_mutex_lock(&mutex);
    if (ticket > 0)
    {
      usleep(1000);
      printf("%s sells ticket:%d\n", id, ticket);
      ticket--;
      //解锁
      pthread_mutex_unlock(&mutex);
    }
    else
    {
      //如果没票了，也要解锁
      pthread_mutex_unlock(&mutex);
      break;
    }
  }
}

int main( void  )
{
  pthread_t t1, t2, t3, t4;

  pthread_mutex_init(&mutex,NULL);

  pthread_create(&t1, NULL, route, "thread 1");
  pthread_create(&t2, NULL, route, "thread 2");
  pthread_create(&t3, NULL, route, "thread 3");
  pthread_create(&t4, NULL, route, "thread 4");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  pthread_mutex_destroy(&mutex);

  return 0;
}
//从打印的结果看以看到
//造成了死锁，什么是死锁，就是线程抓住一个资源不放
//从而导致其他线程无法进入临界区
