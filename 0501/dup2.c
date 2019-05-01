#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
  int fd = open("./tmp.txt",O_CREAT|O_RDWR|O_TRUNC,S_IRUSR|S_IWUSR);
  if(fd<0)
  {
    perror("open error");
    return -1;
  }
  //复制文件描述符功能，通常用于stdin ，stdout,stderr的重定向
  //int dup2(int oldfd,int newfd);
  //dup2用来复制参数oldfd所指的文件描述符，并将oldfd拷贝到参数newfd后一起返回，
  //若参数newfd为一个打开的文件描述符，则newfd所指的文件会先被关闭，
  //若 newfd 等于 oldfd 则返 newfd，而不关闭 newfd所指的文件。
  //dup2所复制的文件描述符与原文的文件描述符共享各种文件状态。
  //共享所有的锁定，读写位置和各项权限或flags.
  //如果成功返回则返回新的文件描述符，出错返回-1.
  int nfd = dup2(fd,1);
  if(nfd<0) 
  {
    printf("Error!\n");
    return -1;
  }

  printf("%d\n",fd);
  fflush(stdout);
  close(fd);

  return 0;
}
