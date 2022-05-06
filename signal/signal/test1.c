#include "head.h"

void sigint_handler(int sig_no)
{
	printf("----%s----\n",__FUNCTION__);
}

int main()
{
	int i = 10;
	signal(SIGRTMIN,sigint_handler);
	
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGRTMIN);
	sigprocmask(SIG_BLOCK,&sigset,NULL);
	while(i--)
	{
		printf("PID is %d,running!\n",getpid());
		sleep(1);
	}
	sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	
	return 0;
}