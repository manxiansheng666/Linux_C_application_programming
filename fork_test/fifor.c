#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define FIFO "/tmp/myfifo"

int main(int argc,char *argv[])
{
	int fd;
	int num;
	mkfifo(FIFO,O_CREAT|O_EXCL);
	char buf[100];
	fd = open(FIFO,O_RDONLY);
	while(1)
	{
		memset(buf,0,100);
		num = read(fd,buf,100);
		printf("rx:%s,fd = %d\n",buf,fd);
		sleep(1);
	}
	close(fd);
}