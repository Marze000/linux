//命令行版本的进度条程序
#include <stdio.h>
#include <stdlib.h>
//只在linux下才有这个文件
#include <unistd.h>

//cache 缓存 vs  buffer 缓冲区
int main()
{

  //使用# 代表的是进度条
  const char* label = "/-\\|";

  char buf[1024]= {0};
  int i = 0;
  for(;i<100;++i)
  {
    buf[i]='#';
    printf("[%d%%][%c][%s]\r",i,label[i%4],buf);//不会另起一行，而是在当前行光标回                                                  到行首
    fflush(stdout);//刷新缓冲区
    usleep(500*1000);
  }
  
  return 0;
}

