#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int listfd,connfd,retval;	
	//pid_t childpid
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	//struct sockaddr cliaddr, servaddr;
	
	listfd = socket(AF_INET, SOCK_STREAM, 0);	    //tcp...connection.../FIFO
	if(listfd<0)
	{
		perror("sock:");
		exit(1);
	}
	
	bzero(&servaddr, sizeof(servaddr)); //Used to initialize memory with zero
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//htonl(INADDR_ANY)
	servaddr.sin_port = htons(8000);	         //TCP protocol HTTP----port
	
	// Typecasting into generic format
	retval = bind(listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval<0)
	{
		perror("bind:");
		exit(2);
	}
	
	listen(listfd,5);
	
	while(1)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listfd, (struct sockaddr *) &cliaddr, &clilen);
		printf("Client connected\n");
	}
}

// htons - Host to Network Short
// inet_addr converts string to 32 bit IP address
