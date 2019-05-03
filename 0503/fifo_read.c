#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  //int mkfifo(const char* pathname , mode_t mdoe);
  //参数： pathname  管道文件的路径名
  //       mode      管道文件的操作权限
  // 返回自： 0  失败 -1；
  umask(0);
  // 创建命名管道
  int ret = mkfifo("./test.fifo",0664);

  //如果错误原因不是‘已经存在’则不会报错，直接执行就行了
  if(ret < 0 && errno != EEXIST)
  {
    perror("mkfifo error");
    return -1;
  }
  
  //以只读方式打开
  int fd = open("./test.fifo",O_RDONLY);
  if(fd <0)
  {
    perror("mkfifo error");
    return -1;
  }
  
  printf("open fifo sucess\n");

  //对管道进行读操作
  while(1)
  {
    char buf[1024] = {0};
    read(fd,buf,1023);
    printf("buf:[%s]\n",buf);
  }

  close(fd);
  return 0;
}
