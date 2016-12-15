#include<signal.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

#define FIFO1 "fifo.1"
#define FIFO2 "fifo.2"
#define MAXBUF 4096

void client(int readfd, int writefd)
{
	char buf[MAXBUF+1];
	ssize_t n;
	char fname[20];
	printf("Enter the filename:\t");
	scanf("%s",&fname);
	printf("The filename is :\t%s\n",fname);
	write(writefd, fname, strlen(fname));
	printf("The contents of the File are:\n");
	while((n=read(readfd, buf, sizeof(buf)))>0)
	{
		buf[n]='\0';
		puts(buf);
	}
}

int  main()
{
	int readfd, writefd;
	writefd = open(FIFO1, O_WRONLY, 0);
	readfd = open(FIFO2, O_RDONLY, 0);
	client(readfd, writefd);
	close(readfd);
	close(writefd);
	return 0;
}
