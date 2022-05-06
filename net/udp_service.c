#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <arpa/inet.h>

int main()
{
	int ret;
	int cfd = socket(AF_INET,SOCK_DGRAM,0);
	if(cfd == -1)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(9999);
	ret = inet_pton(AF_INET,"192.168.1.150",&host_addr.sin_addr.s_addr);
	if(ret == -1)
	{
		perror("inet_pton");
		exit(1);
	}
	
	ret = bind(cfd,(struct sockaddr*)&host_addr,sizeof(host_addr));
	if(ret == -1)
	{
		perror("bind");
		exit(1);
	}
	
	char buf[100];
	char ip[20];
	
	int len;
	struct sockaddr_in client_addr;
	while(1)
	{
//		sendto(cfd,"hello",5,0,(struct sockaddr *)&host_addr,sizeof(host_addr));
		memset(buf,0,100);
		socklen_t addrlen = sizeof(client_addr);
		len = recvfrom(cfd,buf,100,0,(struct sockaddr *)&client_addr,&addrlen);
		if(len <= 0)
		{
			perror("recvfrom");
			exit(1);
		}
		printf("recv is :%s from %s, port %d\n",buf,inet_ntop(AF_INET,&client_addr.sin_addr,ip,20),ntohs(client_addr.sin_port));
	}
	
	close(cfd);
	return 0;
}