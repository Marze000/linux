#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		exit(-1);
	}
	else if(pid == 0)
	{
		while(1)
		{
			printf("i am a child!!\n");	
			sleep(5);
			exit(0);
		}
		
		//exit(0);
	}
	//pid_t wait (int *status);
	//阻塞等待任意一个子进程退出
	//statu：用于获取子进程的退出码//不关注则置空
	//返回值：退出的子进程pid	
	//wait(NULL);//如果当前没有子进程退出，就会一直等待！
	//如果没有wait就会产生僵尸进程，父进程接受不到子进程的退出信息
	
	int ret = waitpid(pid,NULL,0);
	//pid ==-1 等待任意子进程   >0等待指定子进程
	//statu 用于获取子进程退出码，不关注则置空
	//option：（1）0 ： 阻塞等待子进程退出  WNOHANG 将waitpid 设置为非阻塞
	//返回值：>0 退出的子进程pid ；==0：当前没有子进程退出；<0:出错


	if(ret <0 )
	{
		perror("waitpid error");
		return -1;
	}
	printf("pid:%d-%d\n",ret,pid);
	while(1)
	{
		printf("------------i am parent~\n");
		sleep(1);
	}

	return 0;
}
