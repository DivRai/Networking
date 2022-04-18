#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 8000
#define MAXSZ 100

int main()
{
	int sockfd;
	int newsockfd;

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	int n;
	char msg[MAXSZ];
	int clientAddressLength;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	memset(&serverAddress,0 ,sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port= htons(PORT);

	bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

	//listen for connection
	listen(sockfd,5);

	//accept a connection
	while(1)
	{
		printf("\n*********server waiting for new client connection:*****\n");
		clientAddressLength=sizeof(clientAddress);
		newsockfd = accept(sockfd,(struct sockaddr*)&clientAddress, &clientAddressLength);

		//receive from client
		while(1)
		{
			n= recv(newsockfd,msg,MAXSZ,0);
			if(n==0)
			{
			close(newsockfd);
			break;
			}
			msg[n]=0;
			send(newsockfd,msg,n,0);
			printf("Receive and set:%s\n",msg);
		} //close interior while
	} //close exterior while
	return 0;
}
