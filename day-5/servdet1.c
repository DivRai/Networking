/* To get the details of the hosts. Version: 1.0  */

#include<netdb.h>
#include<stdio.h>

void main()
{
	char **name;
	int i;
	
	struct servent *se = NULL;
	while((se = getservent()) != NULL)
	{
		printf("-----------------\n");
		printf(" Offical Service Name = %s\n", se->s_name);
		printf("Port no = %d\n", ntohs(se->s_port));
		printf("Protocol = %s\n", se->s_proto);
		name = se->s_aliases;
		for(i=0;name[i] != NULL; i++)
			printf("........%s..........", name[i]);
		printf("................\n");
	}
}
