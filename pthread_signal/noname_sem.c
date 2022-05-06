#include "head.h"

sem_t sem_empty,sem_full;
char buff[100];

void *func1(void *arg)
{
//	printf("----%s----\n",__FUNCTION__);
	while(1)
	{
		sem_wait(&sem_full);
		fprintf(stderr,"rx:%s",buff);
		sem_post(&sem_empty);
	}
}


int main()
{
	pthread_t tid;
	
	sem_init(&sem_empty,0,1);
	sem_init(&sem_full,0,0);
	
	pthread_create(&tid,NULL,func1,NULL);
	while(1)
	{
		sem_wait(&sem_empty);
		bzero(buff,100);
		printf("tx:");
		fgets(buff,100,stdin);
		sem_post(&sem_full);
	}
	return 0;
}