#include "head.h"

int main()
{
	pid_t pid;
	scanf("%d",&pid);
	
	union sigval a;
	bzero(&a,sizeof(a));
	a.sival_int = 100;
	sigqueue(pid,SIGINT,a);
	
	return 0;
	
}