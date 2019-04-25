#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
	int ret = fork();
	if(ret<0)
	{
		perror("fork");
	}
	else if(ret==0)
	{
		printf("i am  child:%d,ret:%d!\n",getpid(),ret);	
	}
	else
	{
		printf("i am parent:%d,ret:%d!\n",getpid(),ret);
	}
	sleep(1);

	return 0;
}
