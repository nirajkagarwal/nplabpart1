#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int port, sockfd;
	struct sockaddr_in localSock;
	struct ip_mreq group;
	char buf[256];
	printf("Enter the port number:\t");
	scanf("%d",&port);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	int reuse=1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	memset((char *)&localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(port);
	localSock.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *)&localSock, sizeof(localSock));
	group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
	group.imr_interface.s_addr = INADDR_ANY;
	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
	read(sockfd, buf, sizeof(buf));
	printf("Reading Datagram Message:\t\"%s\"\n",buf);
	close(sockfd);
	return 0;
}
