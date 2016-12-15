#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int sockfd, clilen, n, port;
	char fname[50], host[20];
	char buf[256];
	struct sockaddr_in server;
	printf("\nEnter the server IP:\n");
	scanf("%s",&host);
	printf("Enter the port no:\t");
	scanf("%d",&port);	
	getchar();
	printf("Enter the filename:\t");
	scanf("%s",&fname);
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	bzero((struct sockaddr *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	connect(sockfd, (struct sockaddr *)&server, sizeof(server));
	n = write(sockfd, fname, strlen(fname));
	printf("Waiting for file contents....\n");
	while(1)
	{
		bzero(buf, sizeof(buf));
		n = recv(sockfd, buf, 100, 0);
		if(n==-1)
			perror("Socket receiving error");
		if(n==0)
			break;
		puts(buf);
	}
	printf("File contents Received\n");
	close(sockfd);
	return 0;
}
