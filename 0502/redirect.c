/*文件描述符的分配规则和基本重定向原理
 *重定向：重定向的是文件描述符，改变了文件描述符所对应的文件描述信息
 *        这时候对描述符写入数据，数据就会从原本要写入的文件流向新的文件；
 *\n 刷新缓冲区仅仅针对的是标准输出文件，对于其他磁盘文件并不具备刷新缓冲区效果
 *  系统调用因为没有缓冲区，所以不会执行刷新缓冲区的任务
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  close(1);
  //标准输出文件被关闭,无法打印到显示器
  int fd = open("./tmp.txt",O_RDWR|O_CREAT,0664);
  if(fd<0)
  {
    perror("open error");
    return -1;
  }

  //int dup2(int oldfd,newfd);
  //
  printf("fd:%d\n",fd); //数据被放到stdout的缓冲区
  //  \n 对磁盘文件不具备刷新缓冲区的效果
  fflush(stdout);//刷新缓冲区
  

  close(fd);

  return 0;
}
