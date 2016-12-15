#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

int main()
{
	int sockfd, len, port;
	int i, j, status, sendsize=5, recvsize, temp1;
	char str[20], frame[20],temp[20],ack[20],sendwin[20];
	char *msg = "network programming";
	struct sockaddr_in server, client;
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero((struct sockaddr *)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(sockfd, (struct sockaddr *)&server, sizeof(server));
	printf("\nThe msg is:\t%s\n",msg);
	printf("Len = %d \n",strlen(msg));
	i=0;
	sendsize = 5;
	while(i<strlen(msg))
	{
		memset(frame, 0, 20);
		strncpy(frame, msg+i, sendsize);
		printf("\nSending Frame = %s\nSending Window: Start SeqNo: %d \t End SeqNo = %d\n",frame, i, i+sendsize-1);
		send(sockfd, frame, strlen(frame),0);
		printf("\n Sent data....\nWaiting for Acknowledgement...\n");
		memset(ack, 0, 20);
		recv(sockfd, ack, 100, 0);
		sscanf(ack, "%d",&status);
		printf("\nRecvd ack no = %d\n",status);
		i = status;
	}
	write(sockfd, "Exit", sizeof("Exit"));
	printf("\nExiting!!!\n");
	close(sockfd);
	return 0;
}
