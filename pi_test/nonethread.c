#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void calculation(int interval)
{
	unsigned int seed = time(NULL);
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
	for(int i = 0;i < 10;i++)
	{
		calculation(100*(i+1));
	}
	return 0;
}