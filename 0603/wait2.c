#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0){
        printf("iam a child:%d\n",getpid());
        sleep(2);
        _exit(5);
    }else if(pid > 0){
        sleep(3);
        int status;
        printf("iam a father:%d\n",getpid());
        int ret  = wait(&status);
        if(WIFEXITED(status) && ret > 0){
            printf("child return code is :%d\n",
                    WEXITSTATUS(status));
        }else{
            printf("wait child failed\n");
            return 1;
         }
        printf("等待子进程的pid为：%d\n",pid);
    }else{
        perror("fork");
        _exit(-1);
    }
    return 0;
}
