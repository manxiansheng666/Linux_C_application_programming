#include "head.h"

struct msgbuf
{
	long mtype;
	char buf[100];
};

int main()
{
	struct msgbuf msg;
	char send_len;
	key_t keyid = ftok(".",0);
	
	
	int msgid = msgget(keyid,IPC_CREAT|0666);
	
	while(1)
	{
		bzero(&msg,sizeof(struct msgbuf));
		msgrcv(msgid,&msg,100,1,0);
		printf("%s",msg.buf);
	}
	return 0;
	
}