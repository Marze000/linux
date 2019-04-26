#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	printf("before pid id %d\n",getpid());

	 
	if((pid = fork())==-1)
	{
		perror("fork()");
		exit(0);

	}
	else 
	{
		printf("Afert pid is :%d fork return is %d\n",getpid(),pid);
	}
	sleep(1);
	return 0;
}
