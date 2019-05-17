#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int have_noddle = 0;
pthread_cond_t cond_make;
pthread_cond_t cond_eat;
pthread_mutex_t mutex;

void* eat_noddle(void* arg)
{
  while(1) 
  {
    pthread_mutex_lock(&mutex);
    if(have_noddle == 0)
    {
      //没面，要等待
      pthread_cond_wait(&cond_eat,&mutex);
      //该函数集合了三步，解锁，休眠，加锁
    }
    printf("delicious!!\n");
    have_noddle = 0;
    //唤醒
    pthread_cond_signal(&cond_make);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void* make_noddle(void* arg)
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(have_noddle == 1)
    {
      pthread_cond_wait(&cond_make,&mutex);
      //有面没人吃，陷入等待，因为不符合做面的条件
    }
    printf("make a noddle!\n");
    have_noddle = 1;
    pthread_cond_signal(&cond_eat);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main()
{
  pthread_t etid;
  pthread_t mtid;
  
  pthread_mutex_init(&mutex,NULL);

  pthread_cond_init(&cond_eat,NULL);
  pthread_cond_init(&cond_make,NULL);

  int ret = pthread_create(&etid,NULL,eat_noddle,NULL);
  if(ret != 0)
  {
    printf("thread creat error\n");
    return -1;
  }

  
  ret = pthread_create(&mtid,NULL,make_noddle,NULL);
  if(ret != 0)
  {
    printf("thread create error\n");
    return -1;
  }

  pthread_join(etid,NULL);
  pthread_join(mtid,NULL);

  pthread_cond_destroy(&cond_eat);
  pthread_cond_destroy(&cond_make);
  pthread_mutex_destroy(&mutex);

  return 0;
}

