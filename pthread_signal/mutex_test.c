#include "head.h"

pthread_mutex_t lock;

void *func(void *arg)
{
	char *p = (char*)arg;
	pthread_mutex_lock(&lock);
	while(*p != '\0')
	{
		fprintf(stderr,"%c",*p++);
		usleep(500000);
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid1,tid2,tid3;
	
	pthread_mutex_init(&lock,NULL);
	
	pthread_create(&tid1,NULL,func,"AAAAAAAAAA");
	pthread_create(&tid2,NULL,func,"BBBBBBBBBB");
	pthread_create(&tid3,NULL,func,"CCCCCCCCCC");
	
	sleep(50);
	pthread_exit(NULL);
	
}