#include "head.h"

#define SIZE 100

int main()
{
	key_t keyid = ftok(".",0);
	
	int shmid = shmget(keyid,SIZE,IPC_CREAT|0666);
	
	char *p = shmat(shmid,NULL,0);
	
	printf("%s",p);
	
	shmdt(p);
	
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
	
}