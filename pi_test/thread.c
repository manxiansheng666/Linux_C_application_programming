#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void* func1(void *arg)
{
	unsigned int seed = time(NULL);
	int interval = *(int *)arg;
	int sum_count = interval * interval;
	int circular_count = 0;
	double pi;
	for(int i = 0;i < sum_count;i++)
	{
		double x = (double)rand_r(&seed) / RAND_MAX;
		double y = (double)rand_r(&seed) / RAND_MAX;
		if(x*x + y*y <= 1)
		{
			circular_count++;
		}
	}
	pi = 4.0*circular_count/sum_count;
	printf("inside circle num is %d,outside num is %d,pi is %f\n",circular_count,sum_count,pi);
}

int main()
{
	pthread_t tid[10];
	int argv[10];
	for(int i = 0;i < 10;i++)
	{
		argv[i] = 100*(i+1);
		pthread_create(tid+i,NULL,func1,argv+i);
	}
	for(int i = 0;i < 10;i++)
	{
		pthread_join(tid[i],NULL);
	}
	return 0;
}