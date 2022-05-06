#include "thread_pool.h"

void *mytask(void *arg)
{
	int n = (int)arg;
	
	printf("[%u][%s] ==> job will be done in %d sec...\n",\
		(unsigned)pthread_self(),__FUNCTION__,n);

	sleep(n);
	
	printf("[%u][%s] ==> job done!\n",(unsigned)pthread_self(),__FUNCTION__);
	
	return NULL;
}



void *count_time(void *arg)
{
	int i = 0;
	while(1)
	{
		printf("sec is %d\n",i++);
		sleep(1);
	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,count_time,NULL);
	
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool,2);
	
	printf("throwing 3 tasks...\n");
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));

	printf("current thread number:%d\n",remove_thread(pool,0));
	sleep(9);
	
	printf("throwing another 2 tasks...\n");
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));
	
	add_thread(pool,2);
	sleep(6);

	printf("current thread number:%d\n",remove_thread(pool,3));
	
	destroy_pool(pool);
	return 0;
}