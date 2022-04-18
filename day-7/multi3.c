#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include<fcntl.h>

void main()
{
	int fd1,fd2;
	fd_set read_set, write_set, except_set;
	char buf[10];
	
	struct timeval timeout;
	
	int n;
	timeout.tv_sec = 90;
	
	fd1 = open("./srv1",O_RDWR);
	fd2 = open("./cli1",O_RDWR);
	
	FD_ZERO(&read_set);
	
	FD_SET(fd1,&read_set);
	FD_SET(fd2,&read_set);
	
	n = select(FD_SETSIZE,&read_set,NULL,NULL,&timeout);
	if(n<0)
	{
		perror("select");
		exit(1);
	}
	// test whether fd1 is ready or not
	if(FD_ISSET(fd1,&read_set))
	{	
		printf("reading from fd1 (srv1)\n");
		n = read(fd1,buf,10);
		printf("read %d from srv1\n",n);
	}
	
	// test whether fd2 is ready or not
	if(FD_ISSET(fd2,&read_set))
	{	
		printf("reading from fd2 (cli1)\n");
		n = read(fd2,buf,10);
		printf("read %d from cli1\n",n);
	}
}
