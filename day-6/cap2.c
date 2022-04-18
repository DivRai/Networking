#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>
#include<unistd.h>

void main()
{
	int pack_socket,n;
	struct sockaddr_ll sa;
	socklen_t sl;
	char buf[2000];
	sl = sizeof(struct sockaddr_ll);
	
	// sock_raw keeps physical layer header, sock_dgram removes it
	pack_socket = socket(PF_PACKET,SOCK_DGRAM,htons(ETH_P_ALL));
	if(pack_socket<0)
	{
		printf("Failed to open packet socket\n");
		exit(0);
	}
	printf("Packet socket successfully opened\n");
	while(1)
	{
		n = recvfrom(pack_socket,buf,2000,0,(struct sockaddr *)&sa,&sl);
		printf("Received packet of length %d\n",n);
	}
	close(pack_socket);
}
//Use sudo ./a.out to run 
