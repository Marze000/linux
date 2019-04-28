#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/fs.h>
int main()
{
  //FILE *fopen (const char* path ,const char* mode);
  char *file = "/home/maze/study/test.txt";
  FILE *fp = fopen(file,"r+");
  if(fp ==NULL)
  {
    perror("fopen error");
    return -1;
  }
 
  //size_t fwrite(const void*ptr,size_t size,size_t nmemb,FILE* stream) 
  //ptr:要写入的数据
  //size:数据块的大小 
  //nmemb:数据块个数
  //stream : 文件流指针
  //char *buf = "maze is a studying";
  char buf[1024] = "i think it is a thing that will true";
  fwrite(buf,strlen(buf),1,fp);
  //sizeof(buf)作为这个参数的意思是每一个位置都要写满
  //strlen(buf)作为这个参数的意思是只写入buf长度的位置
  

  fseek(fp,0,SEEK_SET);
  //fseek(FILE *stream,long offset,int whence)
  //stream 文件流指针
  //offset 偏移量
  //whence 偏移量的起始位置
  //SEEK_CUR:当前读写位置
  //SEEK_END:文件末尾位置
  //SEEK_SET:文件起始位置
    
  memset(buf,0x00,1024);
  //size_t fread(void* ptr,size_t size,size_t nmemb,FILE *stream)
  int ret = fread(buf,1023,1,fp);
  perror("fread error\n");
  printf("buf:[%d]\n",ret);
  //如果读到了文件末尾，打印end of file
  if(feof(fp))
  {
    printf("end of file");
    return -1;
  }
  fclose(fp) ;

  return 0;
}
