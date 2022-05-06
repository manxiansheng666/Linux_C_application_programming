#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int ret;
	int pipe_fd[2];
	int child;
	char buff[100] = {0};
	if(argc != 2)
	{
		printf("arg is error!\n");
		exit(1);
	}
	
	ret = pipe(pipe_fd);
	if(ret < 0)
	{
		perror("pipi");
		exit(1);
	}
	
	child = fork();
	if(child == 0)
	{
		printf("this is child thread!\n");
		sleep(1);
		read(pipe_fd[0],buff,100);
		printf("rx:%s\n",buff);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(1);
	}
	else
	{
		printf("this is parent thread!\n");
		write(pipe_fd[1],argv[1],strlen(argv[1]));
		write(pipe_fd[1],argv[1],strlen(argv[1]));
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exit(0);
}