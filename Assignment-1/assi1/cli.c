#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8000

int main()
{
    int sockfd;
    char string[100];
    char *str ;
    struct sockaddr_in srvadd;
   
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&srvadd,0,sizeof(srvadd));
       
    srvadd.sin_family = AF_INET;
    srvadd.sin_port = htons(PORT);
    srvadd.sin_addr.s_addr = INADDR_ANY;
       
    while(1)
    {
        int n, len;
        printf("Enter message you want to send to server: ");
        fgets(string,100,stdin);
        
        sendto(sockfd,(const char *)string, strlen(string), MSG_CONFIRM, (const struct sockaddr *) &srvadd, sizeof(srvadd));
            
        n = recvfrom(sockfd, (char *)string,100,MSG_WAITALL,(struct sockaddr *)&srvadd,&len);
        string[n] = '\0';
        printf("Server sent toggled value: %s\n",string);
    }
    return 0;
}
