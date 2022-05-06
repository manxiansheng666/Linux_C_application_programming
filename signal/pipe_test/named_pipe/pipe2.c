/*================================================================
*   Copyright (C) 2021 IEucd Inc. All rights reserved.
*   
*   文件名称：pipe2.c
*   创 建 者：song qingde
*   创建日期：2021年11月07日
*   描    述：
*
================================================================*/

#include "head.h"

int main(void)
{
	char buf[100];
	
	int fd = open("./fifo", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	
	while(1)
	{
		printf("reading!\n");
		bzero(buf,100);
		read(fd,buf,100);
		printf("%s",buf);
	}
	return 0;
}