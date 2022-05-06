#include "head.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;

int balence = 0;


void *func(void *arg)
{
	pthread_mutex_lock(&lock);
	while(balence < 100)
	{
		pthread_cond_wait(&cond,&lock);
	}
	balence -= 100;
	fprintf(stderr,"id get 100,the rest is %d\n",balence);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}


int main()
{
	pthread_t tid;
	
	for(int i = 0;i < 5;i++)
	{
		pthread_create(&tid,NULL,func,(void *)i);
	}
	sleep(2);
	pthread_mutex_lock(&lock);
	balence = 400;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&lock);
	printf("parent put 400\n");
	pthread_exit(NULL);
}