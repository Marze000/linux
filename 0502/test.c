//缓冲区：
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <fcntl.h>

int main()
{
  printf("printf");//先被写到缓冲区

  fprintf(stdout,"%s","fprintf");

  fwrite("wfrite",6,1,stdout);

  write(1,"write",5);//直接将数据写入；

  fflush(stdout);

  sleep(3);
  return 0;

}
