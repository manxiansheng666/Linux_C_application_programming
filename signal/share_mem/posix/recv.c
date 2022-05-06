#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <sys/mman.h>
#include <unistd.h>
       #include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	int fd;
	char *p = NULL;
	char *base = NULL;
	fd = shm_open("/sharemem", O_RDWR , 0666);
	ftruncate(fd, 10);
	base = (char *)mmap(NULL,10,PROT_READ,MAP_SHARED,fd,0);
	p = base;
	for(int i = 0;i < 10;i++)
	{
		printf("%d ",*p++);
	}
	printf("\n");
	munmap(base,10);
	while(1)
		sleep(100);
	return 0;
}