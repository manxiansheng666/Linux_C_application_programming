#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid1;
pthread_t tid2;
void *func(void *arg)
{
	sleep(1);
	
}

int main()
{
    tid2 = pthread_self();
    pthread_create(&tid1,NULL,func,NULL);
	sleep(100);
	pthread_exit(NULL);
}
