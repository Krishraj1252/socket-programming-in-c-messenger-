/*
 *  untitled.h
 *
 *
 *  Created by Ankush Mittal on 01/03/15.
 *  Copyright 2015 IIT. All rights reserved.
 *
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX 100

char s[MAX];
    char sendBuff[MAX];
void communicate(int connfd)
{



 while(1)
 {

     read(connfd,s, sizeof(s));
    printf("Server: %s \n", s); fflush(stdout);
    printf("Client: ");
fgets(sendBuff,MAX,stdin);
    write(connfd,sendBuff, sizeof(sendBuff));

 }

}

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
   int temp;
    struct sockaddr_in serv_addr;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }

    memset(s, '0',sizeof(s));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9091);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	printf("Server address used is: %s\n", argv[1]);
   // if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    //{
      //  printf("\n inet_pton error occured\n");
       // return 1;
    //}

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    }
communicate(sockfd);
    return 0;
}
