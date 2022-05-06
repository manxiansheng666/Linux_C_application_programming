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
	int fd = open(FIFO,O_WRONLY|O_NONBLOCK);
	write(fd,argv[1],strlen(argv[1]));
	close(fd);
	unlink(FIFO);
}