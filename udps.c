#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

int main()
{
	int port, sockfd, n, i;
	struct sockaddr_in server, client;
	char buf[256];
	int clilen = sizeof(client);
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	printf("SERVER IS UP and RUNNING......\n");
	for(i=0;i<10;i++)
	{
		recvfrom(sockfd, buf, 100, 0, (struct sockaddr *)&client, &clilen);
		printf("Received from Packet from %s with Content:\n",inet_ntoa(client.sin_addr));
		puts(buf);
	}
	close(sockfd);
	return 0;
}
