#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func1(void *arg)
{
	
	printf("pid is %d,tid is %ld\n",getpid(),pthread_self());
	printf("hello \n");

	pthread_exit(NULL);
}

int main()
{
	
	pthread_t tid;
	
	pthread_create(&tid,NULL,func1,NULL);
	pthread_detach(tid);
	printf("pid is %d,tid is %ld\n",getpid(),pthread_self());
	sleep(30);
	pthread_exit(NULL);
}
