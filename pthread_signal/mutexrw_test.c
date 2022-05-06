#include "head.h"

pthread_rwlock_t lock;

void *func(void *arg)
{
	char *p = (char*)arg;
	pthread_rwlock_wrlock(&lock);
	while(*p != '\0')
	{
		fprintf(stderr,"%c",*p++);
		usleep(10000);
	}
	pthread_rwlock_unlock(&lock);
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid1,tid2,tid3;
	
	pthread_rwlock_init(&lock,NULL);
	
	pthread_create(&tid1,NULL,func,"AAAAAAAAAA");
	pthread_create(&tid2,NULL,func,"BBBBBBBBBB");
	pthread_create(&tid3,NULL,func,"CCCCCCCCCC");
	
//	sleep(50);
	pthread_exit(NULL);
}