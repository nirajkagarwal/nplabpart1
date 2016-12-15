#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
	int sockfd, newsockfd, clilen, port, n;
	char fname[50], buf[100];
	FILE *fptr;
	struct sockaddr_in server, client;
	
	printf("\nEnter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	printf("The Server is Up and Running....\nWaiting for Client\n");
	listen(sockfd, 5);
	clilen = sizeof(client);
	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)&client, &clilen);
		bzero(fname, 20);
		close(sockfd);
		n = read(newsockfd, fname, 20);
		printf("The file request is :\t%s\n", fname);
		fptr = fopen(fname, "r");
		if(fptr==NULL)
		{
			printf("FILE DOESN'T EXIST.....");
			strcpy(buf, "FILE DOESN'T EXIST....");
			send(newsockfd, buf, strlen(buf),0);
			fclose(fptr);
			close(newsockfd);
			_exit(1);
		}
		while(!feof(fptr))
		{
			fgets(buf, 79, fptr);
			send(newsockfd, buf, strlen(buf),0);
		}
		printf("File Contents Transferred\n");
		fclose(fptr);
		close(newsockfd);
		exit(0);
	}
	return 0;
}
