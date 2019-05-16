#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int Split(char input[],char* output[])
{
  char* p = strtok(input," ");
  int i = 0;
  while(p != NULL)
  {
    output[i] = p; 
    p = strtok(NULL," ");
    ++i;
  }
  return i; 
}

int main()
{
  while(1)
  {
    //1.打印一个命令行输入提示，并且输入指令
    printf("[maze@localhost ~]$ ");
    fflush(stdout);

    char command[1024] = {0};
    //一次读取一行
    gets(command);

    char* argv[1024] = {0};
    int n = Split(command,argv);
    
  }
  return 0;
}
