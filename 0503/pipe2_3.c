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

  //所有的写端被关闭，则读端返回0字节长度
  //在子进程中进行读
  else if(pid == 0)
  { 
    sleep(1);
    close(pipefd[1]);
    char buf[1024] ={0};
    int ret = read(pipefd[0],buf,1023);
    //从第一个参数里面去读数据，读到buf中，大小为1023
    printf("buf : %s--%d\n",buf,ret);

    memset(buf,0x00,strlen(buf));
    ret = read(pipefd[0],buf,1023);
    printf("buf : %s--%d\n",buf,ret);
  }

  //在父进程中进行写
  else
  { 
    char *ptr = "今天是谷雨i~~";
    write(pipefd[1],ptr,strlen(ptr)); 

    close(pipefd[1]);

    //sleep 的意思是保证语句不会出错，所以不让write去写 
    sleep(1000); //父进程一直不会写

    //把数据 ptr 写入到pipefd[1]，写入strlen(str)的长度
  }
  return 0;
}
