//自主实现minishell
//1.获取标准输入
//2.解析输入得到[命令名]+[运行参数]
//3.创建子进程,子进程中进行程序替换
//4.进程等待
//
//minishell中重定向的实现，在原有字符串解析完毕的情况，通过[ls -l>a.txt]
//解析之后获得argv["ls","-l",">","a.txt",NULL]
//判断argv中是否有》》 》来决定是否需要重定向
//dup2(fd,1)将标准输出到指定文件
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <wait.h>

int main()
{
  while(1) 
  {
    char buf[1024] = {0};
    printf("[user@localhost]$ ");
    fflush(stdout);//刷新标准输出缓冲区，把输出缓冲区里的东西打印到输出设备上
    //如果没有这条语句上面的内容不会打印，只有在退出的时候刷新缓冲区才会打印
    
    if(scanf("%[^\n]%*c",buf)!=1)
    {
      getchar();
      continue;//解析失败如果往下执行会形成僵尸进程
    }
    //%[^\n]  意思是从缓存区取数据时遇到\n才会结束，
    // 但是缓冲区会有一个\n，但是无法取出，导致sacnf非阻塞， 
    //%*c     意思是：从缓冲区取一个字符出来丢弃；
    printf("buf:[%s]\n",buf);
   
    int argc = 0;
    char *argv[32];
    char *ptr = buf;
    while(*ptr != '\0')
    {
       if(!(isspace(*ptr)))
       {
          argv[argc++] = ptr; 

          while(!isspace(*ptr)&& *ptr!='\0')
          {
             ptr++;  
          }
         
          *ptr = '\0'; 
          printf("argv[%d]=[%s]\n",argc,argv[argc-1]);
       }
       ptr++;  
    }
    argc[argv] = NULL;
  
    //实现shell内建命令
    if(strcmp(argv[0],"cd")==0) 
    {
      //改变当前工作路径  int chdir(const char* path)
      chdir(argv[1]);
      continue;
    }

    int pid = fork();
    if(pid<0)
    {
      perror("fork error");
      return -1;
    }
    else if(pid == 0)
    {
      int i;
     
      // ls  -l > a.txt
      for(i = 0;i<argc;++i)
      {
        if(strcmp(argv[i],">")==0)
        {
          int fd = open(argv[i+1],O_CREAT | O_WRONLY | O_TRUNC,0664);
          dup2(fd,1);
          argv[i] = NULL;
        }
        else if(strcmp(argv[i],">>")==0)
        {
          int fd = open(argv[i+1],O_WRONLY|O_CREAT |O_APPEND,0644);
          dup2(fd,1);
          argv[i] = NULL;
        }
      }
      execvp(argv[0],argv);
      exit(-1);
    }
    
    wait(NULL); 
  
   }
   return 0;
}
