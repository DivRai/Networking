#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100

int main()
{
	int sockfd;
	struct sockaddr_in serverAddress;

	char msg1[MAXSZ];
	char msg2[MAXSZ];

	int n;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	memset(&serverAddress,0 ,sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddress.sin_port= htons(PORT);

	connect(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

	while(1)
	{
		printf("\nEnter message to send to server:\n");
		fgets(msg1,MAXSZ,stdin);
		if(msg1[0]=='#')
		break;

		n=strlen(msg1)+1;
		send(sockfd,msg1,n,0);

		n=recv(sockfd,msg2,MAXSZ,0);

		printf("Receive message from server:%s\n",msg2);
	}
	return 0;
}
