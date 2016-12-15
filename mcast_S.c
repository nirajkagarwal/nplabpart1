#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
	char msg[] = "I am the best";
	int port, sockfd;
	struct sockaddr_in groupSock;
	struct in_addr localInterface;
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset((char *)&groupSock, 0, sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_port = htons(port);
	groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");
	localInterface.s_addr = INADDR_ANY;
	setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));
	sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&groupSock,sizeof(groupSock));
	return 0;
}
