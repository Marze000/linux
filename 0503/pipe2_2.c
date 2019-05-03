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

  //所有读端被关闭，写端会触发异常，导致进程退出
  else if(pid == 0)
  { 
    close(pipefd[0]);
    sleep(1000);
    char buf[1024] ={0};
    read(pipefd[0],buf,1023);
    printf("buf : %s\n",buf);
  }

  //在父进程中进行写
  else
  {
    close(pipefd[0]);
    //先睡眠3秒，保证子进程的读端被关闭
    sleep(3);
    char *ptr = "今天是谷雨i~~";
    write(pipefd[1],ptr,strlen(ptr)); 
    //把数据 ptr 写入到pipefd[1]，写入strlen(str)的长度
    
    //如果write正常的话，就会睡眠1000秒，否则直接退出
    sleep(1000);
  }
  
  
  printf("+-------end\n");
  return 0;
}
