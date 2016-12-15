#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
	int port,n,i, sockfd;
	char buf[256], host[20];
	struct sockaddr_in server;
	printf("Enter the server IP:\t");
	scanf("%s",&host);
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	printf("Sending Packets....\n");
	for(i=0;i<10;i++)
	{
		printf("This is packet %d\n", i+1);
		sprintf(buf, "This is packet %d\n", i+1);
		sendto(sockfd, buf, sizeof(buf), 0, &server, sizeof(server));
	}
	close(sockfd);
	return 0;
}
