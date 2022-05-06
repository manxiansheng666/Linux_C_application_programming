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

int main()
{
	int shmid = shmget(ftok(".",0),10,IPC_CREAT|0666);
	
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
	
	
	char *p = shmat(shmid,NULL,0);
	while(1)
	{
		sem_p(semid,FULL);
		printf("%c",*p);
		sem_v(semid,EMPTY);
	}
	return 0;
}