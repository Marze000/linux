#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	extern char** environ;
	char* const Envp[]= {
		"MYpath=/lenv","MYname=maze",NULL
	};
	pid_t id = vfork();
	if(id==0)
	{
		sleep(1);
		printf("i am a child! pid :%d,ppid:%d\n",getpid(),getppid());
		execle("./Env","./Env",NULL,Envp);
		
		exit(1);
	}
	
	else{
		printf("i am a father ! pid:%d,ppid：%d\n",getpid(),getppid());
		printf("----i am a genius -----------\n");
		wait(NULL);
	}
	return 0;
}
