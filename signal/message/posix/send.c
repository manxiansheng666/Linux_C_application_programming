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
	mq_unlink("/hello");
	exit(0);
}

int main()
{
	struct mq_attr mqAttr;
	mqAttr.mq_msgsize = 10;
	mqAttr.mq_maxmsg = 5;
	id = mq_open("/hello", O_CREAT | O_RDWR, 0666,&mqAttr);
	signal(SIGINT,sighandler);
	while(1)
	{
		int ret;
		sleep(3);
		ret = mq_send(id,"hello",6,0);
		if(ret == -1)
		{
			printf("send is fail\n");
		}
		else if(ret == 0)
		{
			printf("send is OK\n");
		}
	}
	return 0;
}