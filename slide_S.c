#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

int main()
{
	int sockfd, ack, port, len, lfd, i;
	char frame[20];
	char frame1[20];
	int sendsize = 5;
	char ack_str[50];
	char *recv_str;
	recv_str = malloc(50);
	srand(time(NULL));
	memset(recv_str, 0, 20);
	int yes = 1;
	struct sockaddr_in server, client;
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr  *)&server, sizeof(server));
	listen(sockfd, 5);
	len = sizeof(&client);
	lfd = accept(sockfd, (struct sockaddr *)&client, &len);
	len = -1;
	i=0;
	for(;;)
	{
		memset(frame, 0, 20);
		recv(lfd, frame, 100, 0);
		if(strcmp(frame, "Exit")==0)
		{
			printf("\nExitting\n");
			break;
		}
		int err = rand()%8;
		printf("%d\n",err);
		int i5;
		if(err<4)
		{
			memset(frame1,0,20);
			for(i5=0;i5<err;i5++)
				frame1[i5] = frame[i5];
			recv_str = (char *) strcat(recv_str,frame1);
			frame[err] = 'x';
			printf("\n\nIntroduce error at a time: %d \tError at: %d\tError Frame:%s\n",err, i+err, frame);
			i = i+err;
			ack = i;
		}
		printf("\n Receiver: Sending ACK back to sender ack = %d", ack);
		sprintf(ack_str, "%d", ack);
		send(lfd, ack_str, strlen(ack_str),0);
	}
	printf("\n Received Final str at Destination = %s\n",recv_str);
	close(sockfd);
}
