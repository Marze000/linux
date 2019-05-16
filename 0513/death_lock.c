/*********************************************************************8*
 *
 * (1)初始化 int pthread_cond_init(pthread_cond_t *restrict cond,
 *                  const pthread_condattr_t *restrict attr);
 *     参数  cond：要初始化的条件变量        attr：NULL
 

  (2)销毁  int pthread_cond_destroy(pthread_cond_t *cond) 1

  (3)等待条件满足 int pthread_cond_wait(pthread_cond_t *restrict cond,
                                        pthread_mutex_t *restrict mutex);
        cond：要在这个条件变量上等待      mutex：互斥量

  (4) 唤醒等待  int pthread_cond_broadcast(pthread_cond_t *cond);
                int pthread_cond_signal(pthread_cond_t *cond);


*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond;//条件变量

pthread_mutex_t mutex;//互斥量

void *r1(void *arg)
{
  while (1)
  {
    pthread_cond_wait(&cond, &mutex);
    printf("活动\n");
  }
}

void *r2(void *arg)
{
  while (1)
  {
    pthread_cond_signal(&cond);
    sleep(1);
  }
}

int main()
{
  pthread_t t1, t2;
  
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&t1, NULL, r1, NULL);
  pthread_create(&t2, NULL, r2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}
