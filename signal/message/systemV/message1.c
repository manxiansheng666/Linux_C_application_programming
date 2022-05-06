#include "head.h"

struct msgbuf
{
	long mtype;
	char buf[100];
};
int main()
{
	char buff[100];
	char send_len;
	key_t keyid = ftok(".",0);
	
	int msgid = msgget(keyid,IPC_CREAT|0666);
	
	while(1)
	{
		struct msgbuf msg;
		bzero(&msg,sizeof(struct msgbuf));
		fgets(msg.buf,100,stdin);
		msg.mtype = 1;
		
		msgsnd(msgid,&msg,100,0);
	}
	return 0;
	
}