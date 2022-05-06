#include "head.h"

#define EMPTY 1
#define FULL 0



void sem_p(int semid,int sem)
{
	struct sembuf a[1];
	a[0].sem_num = sem;
	a[0].sem_op = -1;
	a[0].sem_flg = 0;
	semop(semid,a,1);
}

void sem_v(int semid,int sem)
{
	struct sembuf a[1];
	a[0].sem_num = sem;
	a[0].sem_op = 1;
	a[0].sem_flg = 0;
	semop(semid,a,1);
}

void sigint_handler(int sig_no)
{
	int semid = semget(ftok(".",1),2,0);
	semctl(semid,3,IPC_RMID);
	exit(0);
}

int main()
{
	int shmid = shmget(ftok(".",0),10,IPC_CREAT|0666);
	
	signal(SIGINT,sigint_handler);
	
	char *p = shmat(shmid,NULL,0);
	bzero(p,10);
	char *msg = "0123456789";
	int i = 0;
	
	int semid = semget(ftok(".",1),2,IPC_CREAT|IPC_EXCL|0666);
	if(semid > 0)
	{
		union semun sem;
		sem.val = 1;
		semctl(semid,EMPTY,SETVAL,sem);
		sem.val = 0;
		semctl(semid,FULL,SETVAL,sem);
	}
	else
	{
		semid = semget(ftok(".",1),2,IPC_CREAT|0666);
	}
	
	
	
	while(1)
	{
		sem_p(semid,EMPTY);
		p[0] = msg[i];
		i = (i + 1) % 10;
		sem_v(semid,FULL);
	}
	return 0;
}