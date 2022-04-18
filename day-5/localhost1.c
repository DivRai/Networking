/* To get the details of the hosts. Version: 1.0  */

#include<netdb.h>
#include<stdio.h>
#include<limits.h>

void main(int argy, char *ardv[])
{
	char hostname[HOST_NAME_MAX +1];
	
	hostname[HOST_NAME_MAX] = 0;
	
	if(gethostname(hostname, HOST_NAME_MAX) == 0)
		puts(hostname);
	else
		perror("gethostname");
}
