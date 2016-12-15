#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<sys/stat.h>

#define MAXBUF 4096
#define FIFO1 "fifo.1"
#define FIFO2 "fifo.2"

void server1(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buf[MAXBUF+1];
	n = read(readfd, buf, MAXBUF);
	buf[n]='\0';
	printf("The filename is :\t%s\n",buf);
	fd = open(buf, O_RDONLY, 0);
	while((n=read(fd, buf, MAXBUF))>0)
	{
		write(writefd, buf, n);
	}
	close(fd);
}

int main()
{
	int readfd, writefd;
	printf("Creating pipes....\n");
	mkfifo(FIFO1,0666);
	mkfifo(FIFO2,0666);
	printf("Creating file descriptors....\n");
	readfd = open(FIFO1,O_RDONLY, 0);
	writefd = open(FIFO2, O_WRONLY, 0);
	printf("Created PIPES...\n");
	server1(readfd, writefd);
	close(readfd);
	close(writefd);
	printf("\nJob Completed...\n");
	return 0;
}
