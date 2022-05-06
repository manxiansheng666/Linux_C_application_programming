#include "head.h"

void f(int sig,siginfo_t *info,void *arg)
{
	printf("catch sig:%d\n",sig);
	
	printf("rx arg is %d\n",info->si_int);
	
}

int main()
{
	printf("my PID: %d\n",getpid());
	
	struct sigaction act;
	bzero(&act,sizeof(act));
	
	act.sa_sigaction = f;
	act.sa_flags = SA_SIGINFO;
	
	sigaction(SIGINT,&act,NULL);
	
	pause();
	return 0;
	
}