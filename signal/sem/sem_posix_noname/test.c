#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem_id;

void *f(void * arg)
{
	sem_wait(&sem_id);
	printf("pthread is running!");
	pthread_exit(NULL);
}

int main()
{
	
	sem_init(&sem_id,0,0);
	pthread_t tid;
	pthread_create(&tid,NULL,f,NULL);
	sleep(1);
	sem_post(&sem_id);
	pthread_exit(NULL);
}