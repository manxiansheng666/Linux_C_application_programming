#include "head.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void clean_handler(void *arg)
{
	printf("cancle is OK,and put lock\n");
	pthread_mutex_unlock(&lock);
}

void *func(void *arg)
{
	
	pthread_cleanup_push(clean_handler,NULL);
	
	pthread_mutex_lock(&lock);
	printf("child get lock\n");
	sleep(6);
	printf("child put lock\n");
	pthread_mutex_unlock(&lock);
	
	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid;
//	pthread_mutex_init(&lock,NULL);

	pthread_create(&tid,NULL,func,NULL);
	sleep(1);
//	pthread_cancel(tid);
	pthread_mutex_lock(&lock);
	printf("parent get lock\n");
	sleep(6);
	printf("parent put lock\n");
	pthread_mutex_unlock(&lock);
	
	
	
	pthread_exit(NULL);
}
