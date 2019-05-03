#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/wait.h>

//实现一个管道符 ls | grep make
int main()
{
  int pipefd[2];
  if(pipe(pipefd)<0)
  {
    perror("pipe erroe");
    return -1;
  }

  int pid1 = fork();
  if(pid1 == 0)
  {
    close(pipefd[0]);
    dup2(pipefd[1],1);

    //ls 将目录下的文件信息打印到标准输出
    execlp("ls","ls",NULL);
  }

  //用户在操作管道时没有用到哪一端，则关闭掉
  //将ls 结果作为 grep 的输入
  int pid2 = fork();
  if(pid2 == 0)
  {
    close(pipefd[1]);
    dup2(pipefd[0],0);

    //grep 循环从标准输入读取数据进行字符串匹配
    execlp("grep","grep","make",NULL);
  }

  //父进程的读写端也要关闭
  close(pipefd[0]);
  close(pipefd[1]);

  //等待两个子进程退出
  wait(NULL);
  wait(NULL);

  return 0;
}
