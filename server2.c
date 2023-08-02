/*
 *  server.h
 *
 *
 *  Created by Ankush Mittal
 *  Copyright 2015 IIT. All rights reserved.
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include<pthread.h>
#include<thread>
#include <sys/types.h>
using namespace std;
#define MAX 100
char s[MAX];
    char sendBuff[MAX];
int nRet;
void readfromclient(int connfd)
{
    write(connfd, "Hello. Welcome to our service\n", 100);
 while(1)
 {

     read(connfd,s, sizeof(s));
     printf("Client: %s \n", s);
     fflush(stdout);

 }

}
void writetoclient(int connfd)
{

while(1)
{
 printf("Server: ");
 fgets(sendBuff,MAX,stdin);
 write(connfd,sendBuff, sizeof(sendBuff));
}
}
int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

	int temp;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9091);
    nRet=bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
 if(nRet<0)
exit(EXIT_FAILURE);
    nRet=listen(listenfd ,10);
 if(nRet<0)
exit(EXIT_FAILURE);
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        thread writing(writetoclient,connfd);
        thread reading(readfromclient,connfd);
	reading.join();
	writing.join();

}
