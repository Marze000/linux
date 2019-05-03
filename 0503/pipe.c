#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int fds[2];
  char buf[100];
  int len;

  if(pipe(fds)==-1)
  {
    perror("make pipe");
    exit(-1);
  }

  //read from stdin
  //char* fgets(char *buf,int bufsize,FILE* stream)
  //读取当前行，如果bufsize太小，则分次读取，调用一次fgets最多读取一行
  //参数：*buf    字符型指针，指向用来存储所得数据的地址
  //      bufsize 整形数据，指明存储数据的大小
  //      *stream 文件结构体指针，将要读取的文件流
  while(fgets(buf,100,stdin))
  {
    len = strlen(buf);
    //fds[1]写端  
    if(write(fds[1],buf,len)!=len)
    {
      perror("write to error");
      break; 
    }

    memset(buf,0x00,sizeof(buf));

    //read from pipe         fds[0]读端  
    if((len = read(fds[0],buf,len))==-1)
    {
      perror("read from pipe");
      break;
    }

    //write to stdout
    if(write(1,buf,len)!=len)
    {
      perror("write to stdout");
      break;
    }
  } 

  return 0;
}
