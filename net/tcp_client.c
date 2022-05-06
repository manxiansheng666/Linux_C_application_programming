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
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd == -1)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(8888);
	ret = inet_pton(AF_INET,"192.168.1.150",&host_addr.sin_addr.s_addr);
	if(ret == -1)
	{
		perror("inet_pton");
		exit(1);
	}
	
	ret = bind(cfd,(struct sockaddr*)&client_addr,sizeof(client_addr));
	if(ret == -1)
	{
		perror("bind");
		exit(1);
	}
		
	ret = connect(cfd,(struct sockaddr*)&host_addr,(socklen_t)sizeof(host_addr));
	if(ret == -1)
	{
		perror("connect");
		exit(1);
	}
	
	
	char send_data[20] = {"hello songqingde"};
	int len = strlen(send_data);

	while(1)
	{
		len = write(cfd,send_data,len);
		if(len == -1)
		{
			perror("write");
			break;
		}
		else if(len == 0)
		{
			printf("disconnect!\n");
			break;
		}
		else 
			printf("send OK!\n");
		
		sleep(3);
	}

	
	
	close(cfd);
	
	return 0;
}