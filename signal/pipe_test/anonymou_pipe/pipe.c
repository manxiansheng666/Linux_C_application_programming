/*================================================================
*   Copyright (C) 2021 IEucd Inc. All rights reserved.
*   
*   文件名称：pipe.c
*   创 建 者：song qingde
*   创建日期：2021年11月07日
*   描    述：
*
================================================================*/


#include "head.h"

#define BUFF_SIZE 100

int main()
{
	int fd[2];
	pid_t child;
	pipe(fd);
	char buf[100];
	child = fork();
	if(child == 0)
	{
		
		printf("this is the child thread!\n");
		sleep(1);
		write(fd[1],"hello",5);
	}
	else
	{
		bzero(buf,BUFF_SIZE);
		printf("this is the parent thread!\n");
		read(fd[0],buf,BUFF_SIZE);
		printf("rx:%s\n",buf);
	}
	
	close(fd[0]);
	close(fd[1]);
	return 0;
}
