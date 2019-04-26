#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* agrv[])
{
	extern char** environ;
	int i = 0;
	for(;environ[i];++i)
	{
		printf("%s\n",environ[i]);
	
	}

	return 0;
}
