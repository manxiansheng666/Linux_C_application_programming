#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <arpa/inet.h>

int cfd;
int lfd;

void sighandler(int signo)
{
	printf("----%s----\n",__FUNCTION__);
	close(cfd);
	close(lfd);
	exit(1);
}


int main()
{
	int ret;
	void *retp = NULL;

	char str_buf[20];
	uint16_t cport;
	
	signal(SIGINT,sighandler);
	
	lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(8888);
	host_addr.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(lfd,(struct sockaddr*)&host_addr,sizeof(host_addr));
	if(ret == -1)
	{
		perror("bind");
		exit(1);
	}
	
	ret = listen(lfd,128);
	if(ret == -1)
	{
		perror("listen");
		exit(1);
	}
	
	struct sockaddr_in client_addr;
	socklen_t socklen = sizeof(client_addr);
	cfd = accept(lfd,(struct sockaddr*)&client_addr,&socklen);
	if(cfd == -1)
	{
		perror("accept");
		exit(1);
	}
	
	retp = inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,str_buf,20);
	if(retp == NULL)
	{
		perror("inet_ntop");
		exit(1);
	}
	
	printf("%s connected,and the port is %d\n",str_buf,ntohs(client_addr.sin_port));
	
	char buf[100];
	while(1)
	{
		memset(buf,0,100);
		int len = read(cfd,buf,100);
		if(len == -1)
		{
			perror("read");
			break;
		}
		else if(len == 0)
		{
			printf("client is closeed!\n");
			break;
		}
		printf("client reclive is :%s\n",buf);
	}
	
	close(cfd);
	close(lfd);
	
	return 0;
}