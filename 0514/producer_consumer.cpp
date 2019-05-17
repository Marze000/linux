#include <iostream>
#include <queue>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 8
class BlockQueue
{
private:
    std::queue<int> q;
    int cap;
    pthread_mutex_t lock;
    pthread_cond_t full;
    pthread_cond_t empty;
private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }

    void UnLockQueue()
    {
      pthread_mutex_unlock(&lock);
    }

    //pthread_cond_wait (pthread_cond_t*cond,pthread_mutex_t*mutex)
    //用来等待条件变量被设置，值得注意的是，需要调用一个已经上锁的互斥体mutex
    //这是为了防止在真正进入等待状态之前，别的线程有可能设置该条件变量而产生竞争。
    //生产者等待
    void ProductWait()
    {
      pthread_cond_wait(&full, &lock);
    }
    //消费者等待
    void ConsumeWait()
    {
      pthread_cond_wait(&empty, &lock);
    }

    void NotifyProduct()
    {
      pthread_cond_signal(&full);
    }

    void NotifyConsume()
    {
      pthread_cond_signal(&empty);
    }

    bool IsEmpty()
    {
      return ( q.size() == 0 ? true : false  );
    }
    bool IsFull()
    {
      return ( q.size() == cap ? true : false  );
    }
public:
    BlockQueue(int _cap = NUM):cap(_cap)
    {
       pthread_mutex_init(&lock, NULL);
       pthread_cond_init(&full, NULL);
       pthread_cond_init(&empty, NULL);
    }   

    void PushData(const int &data)
    {
      LockQueue();
      while(IsFull())
      {
        NotifyConsume();
        std::cout << "queue full, notify consume data, product stop." << std::endl;
        ProductWait();
      }

      q.push(data);
      // NotifyConsume();
      UnLockQueue();
    }
    void PopData(int &data)
    {
      LockQueue();
      while(IsEmpty()){
        NotifyProduct();
          std::cout << "queue empty, notify product data, consume stop." <<
          std::endl;
        ConsumeWait();
      }
      data = q.front();
      q.pop();
      // NotifyProduct();
      UnLockQueue();
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&full);
      pthread_cond_destroy(&empty);
    }
};

void *consumer(void *arg)
{
  BlockQueue *bqp = (BlockQueue*)arg;
  int data;
  for( ; ;  ){
    bqp->PopData(data);
    std::cout << "Consume data done : " << data << std::endl;
  }
}

//more faster
void *producter(void *arg)
{
  BlockQueue *bqp = (BlockQueue*)arg;
  srand((unsigned long)time(NULL));
  for( ; ;  )
  {
     int data = rand() % 1024;
     bqp->PushData(data);
     std::cout << "Prodoct data done: " << data << std::endl;
     //sleep(1);
  }
}

int main()
{
  BlockQueue bq;
  pthread_t c,p;
  pthread_create(&c, NULL, consumer, (void*)&bq);
  pthread_create(&p, NULL, producter, (void*)&bq);

  pthread_join(c, NULL);
  pthread_join(p, NULL);
  
  return 0;
}
