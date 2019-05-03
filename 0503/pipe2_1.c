#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//匿名管道只能用于具有亲缘关系的进程间通信
//管道必须创建于子进程之前

int main()
{
  //int pipe(int pipefd[2]);
  //创建管道
  int pipefd[2];

  int ret = pipe(pipefd);
  if(ret <0)
  {
    perror("pipe error");
    return -1;
  }

  //创建子进程实现通信
  int pid = fork();
  if(pid<0)
  {
    perror("fork error");
    exit(-1);
  }

  //在子进程中进行读
  else if(pid == 0)
  { 
    sleep(1000);
    //让读取睡眠1000秒，肯定不会读到
    char buf[1024] ={0};
    read(pipefd[0],buf,1023);
    //从第一个参数里面去读数据，读到buf中，大小为1023
    printf("buf : %s\n",buf);
  }

  //在父进程中进行写
  //由于子进程和父进程不知道哪个先运行，所以是不是子进程先于父进程运行
  //就无法读取到数据呢？
  //答案是：不会，无论哪个先运行，都会读取到数据，不信的话在父进程加个睡眠sleep(3);
  //父进程等待三秒，子进程依然可以读取到数据，，，是因为如果没有执行到write，那么
  //读read会一直阻塞，直到你把它写进去才会执行read
  //也就是如果管道没有数据则read会阻塞，和普通文件不一样，普通文件如果读不到会直接返回0
  else
  {
    //sleep(3);
    int tlen = 0;
    //如果管道数据写满，则write会一直阻塞
    while(1)
    { 
      char *ptr = "今天是谷雨i~~";
      tlen += write(pipefd[1],ptr,strlen(ptr)); //write返回的是写入数据的长度8,不是字节数
      printf("%d\n",tlen);
    }
    //把数据 ptr 写入到pipefd[1]，写入strlen(str)的长度
  }
  return 0;
}
