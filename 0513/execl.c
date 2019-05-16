#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t res = fork();
  if(res == 0)
  {
    printf("由execl替换 \n");
    execl("/usr/bin/ls","ls","/",NULL);
  }

  wait(NULL);

  pid_t ret = fork();
  if(ret == 0)
  {

  }
  printf("afte ls\n");


  return 0;
}
