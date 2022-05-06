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

void sigint_handler(int sig_no)
{
	unlink("./fifo");
	exit(0);
}


int main(void)
{
	char buf[100];
	
	mkfifo("./fifo",O_CREAT | O_RDWR | O_EXCL | 0666);
	
	int fd = open("./fifo", O_RDWR);
	
	signal(SIGINT,sigint_handler);
	
	while(1)
	{
		bzero(buf,100);
		fgets(buf,100,stdin);
		write(fd,buf,strlen(buf));
	}
	return 0;
}