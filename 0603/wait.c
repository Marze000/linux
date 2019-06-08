#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0){
        //child
        printf("iam a child:%d\n",getpid());
        sleep(20);
        _exit(5);
    }else if(pid > 0){
        //father
        int status;
        printf("iam a father:%d\n",getpid());
        int ret  = wait(&status);
        if ( ret > 0 && ( status & 0X7F  ) == 0  ){ // 正常退出
            printf("child exit code:%d\n", (status >> 8) & 0XFF);
        } else if( ret > 0  ) { // 异常退出
             printf("sig code : %d\n", status & 0X7F );
          }
    
        printf("等待子进程的pid为：%d\n",pid);
    }else{
        perror("fork");
        _exit(-1);
    }
    return 0;
}
