#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<wait.h>
#include<string.h>
#include<errno.h>

int main()
{
	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork");
		exit(-1);
	}

	if(pid == 0)
	{
		sleep(20);
		exit(10);
	}
	
	
	return 0;
}
