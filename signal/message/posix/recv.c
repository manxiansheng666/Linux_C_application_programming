#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
mqd_t id;

void sighandler(int sig)
{
	mq_close(id);
	exit(0);
}

int main()
{
	
	id = mq_open("/hello",O_RDWR);
	
	printf("id is %d\n",id);
	signal(SIGINT,sighandler);
	struct mq_attr mqAttr;
    mq_getattr(id, &mqAttr);
	printf("size is %ld\n",mqAttr.mq_msgsize);
	printf("count is %ld\n",mqAttr.mq_maxmsg);
	while(1)
	{
		char buf[10] = {0};
		mq_receive(id,buf,mqAttr.mq_msgsize,NULL);
		printf("recv is %s\n",buf);
	}
	mq_close(id);
	return 0;
}