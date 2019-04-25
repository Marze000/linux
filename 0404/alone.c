#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t id = fork();
	if(id<0)
	{
		perror("fork");
	}
	
	else if(id==0)
	{
		printf("i am a child pid:%d\n",getpid());
		sleep(10);

	}
	else
	{
		printf("i am a praent pid:%d\n",getpid());
		sleep(3);
		exit(0);
	}
	return 0;
}
