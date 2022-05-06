#include "head.h"

sem_t *sem_empty ;
sem_t *sem_full;
void sigint_handler(int sig_no)
{
	sem_close(sem_empty);
	sem_close(sem_full);
	sem_unlink("/empty");
	sem_unlink("/full");
	exit(0);
}

int main()
{
	int shmid = shmget(ftok(".",0),10,IPC_CREAT|0666);
	
	sem_empty = sem_open("/empty",O_CREAT,0666,1);
	sem_full = sem_open("/full",O_CREAT,0666,0);
	
	signal(SIGINT,sigint_handler);
	
	char *p = shmat(shmid,NULL,0);
	bzero(p,10);
	char *msg = "0123456789";
	int i = 0;
	
	while(1)
	{
		sem_wait(sem_empty);
		p[0] = msg[i];
		i = (i + 1) % 10;
		sem_post(sem_full);
	}
	return 0;
}