#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8000

char* toggle(char str[])
{
    char* ret_str=str;
    for(int i=0; i<strlen(str); i++)
    {
        if(ret_str[i]>='A' && ret_str[i]<='Z')
            ret_str[i]=ret_str[i]+32;
        else if(ret_str[i]>='a' && ret_str[i]<='z')
            ret_str[i]=ret_str[i]-32;
    }
    return ret_str;
}

int main()
{
    int sockfd;
    char str[100];
    struct sockaddr_in srvadd,cliadd;
       
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&srvadd,0,sizeof(srvadd));
    memset(&cliadd,0,sizeof(cliadd));
       
    srvadd.sin_family = AF_INET;
    srvadd.sin_addr.s_addr = INADDR_ANY;
    srvadd.sin_port = htons(PORT);
       
    if(bind(sockfd,(const struct sockaddr *)&srvadd,sizeof(srvadd)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    while(1)
    {
        int len, n;
        len = sizeof(cliadd);  
        
        n = recvfrom(sockfd,(char *)str,100,MSG_WAITALL,(struct sockaddr *) &cliadd,&len);
        str[n] = '\0';
        printf("Message from client: %s\n",str);
        char *toggled = toggle(str);
        
        sendto(sockfd,str,strlen(str),MSG_CONFIRM,(const struct sockaddr *) &cliadd,len);
    }
    return 0;
}
