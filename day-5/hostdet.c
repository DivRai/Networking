/* To get the details of the hosts. Version: 1.0  */

#include<netdb.h>
#include<stdio.h>
#include<netinet/in.h>

void main()
{
	struct hostent *he = NULL;
	char dotaddr[20];
	he = gethostbyname("196.12.100.100");
	inet_ntop(AF_INET, he->h_addr, dotaddr,20);
	printf("address in dd notation = %s\n", dotaddr);
}
