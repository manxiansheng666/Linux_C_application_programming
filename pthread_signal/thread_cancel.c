#include "head.h"

void *func(void *arg)
{
	pthread_detach(pthread_self());
	for(int i = 0;i < 1000000;i++)
		for(int j = 0;j < 1000;j++);
	for(int z = 0;z < 1000000;z++)
	{
		fprintf(stderr,"%c",'x');
	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t tid;
	
	pthread_create(&tid,NULL,func,NULL);
	
	pthread_cancel(tid);
	
	pthread_exit(NULL);
}