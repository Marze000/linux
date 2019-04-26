

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid=fork();
	if(pid<0)	
	{
		perror("fork()");
		return 1;
	}
	else if(pid==0)
	{
		printf("child is run,pid is : %d\n",getpid());
		sleep(5);
		exit(257);
	}
	else 
	{
		int status = 0;
		pid_t ret = waitpid(-1,&status,0);
		printf("this is test for wait\n");
		if(WIFEXITED(status)&&ret==pid)
		{
			printf("wait child 5s sucess,child return code is :%d\n",
					WEXITSTATUS(status));
		}
		else
		{
			printf("wait child failed ,return.\n");
			return -1;
		}
	}
	return 0;
}
