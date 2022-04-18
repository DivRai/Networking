// UDP Client Server 

#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int connfd, retval, sockfd, n;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	char buf[10000];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	//UPD Connection -> no listen and accept
	if(sockfd < 0)
	{
		perror("sock:");
		exit(1);
	}

	//memset can also be used in place of bzero
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);

	retval = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval<0)
	{
		perror("bind:");
		exit(2);
	}

	printf("Socket bound to port 8000\n");

	while(1)
	{
		printf("Before recvfrom\n");
		n = recvfrom(sockfd, buf, 10000, 0, (struct sockaddr *)&cliaddr, &clilen);
		printf("Received %d bytes\n", n);
		buf[n] = '\0';
		printf("Message from client = %s\n", buf);
	}
	return 0;
}
