#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
int main() {
	extern char** environ;
	char** ptr;	
	pid_t id = vfork();
	if(id == 0)	{
		sleep(1);
		printf("i am a child ,my id is :%d,ppid is %d\n",
				getpid(),getppid());
		execl("/bin/ls","-a","-l",NULL);
		exit(1);
	}	
	else{
		printf("i am a father ,pid :%d,ppid :%d\n",
				getpid(),getppid());
		printf("--------------\n");
		wait(NULL);
	}
	return 0;
}
