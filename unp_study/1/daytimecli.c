/*************************************************************************
	> File Name: daytimecli.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月14日 星期四 22时37分34秒
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>

#define err_sys perror

int main(int argc ,char **argv){
    int sockfd,n;
    char recvline[1025];
    struct sockaddr_in servaddr;
    if(argc != 2){
        perror("usage: a.out <IPaddress>");
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        err_sys("socket error");
    }
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
        printf("inet_pton error for %s",argv[1]);

    if(connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr))<0){
        err_sys("connect error");
    }
    while((n = read(sockfd,recvline,1024))>0){
        recvline[n]=0;
        if(fputs(recvline,stdout) == EOF)
            err_sys("fputs error");
    }
    if (n<0)
        err_sys("read error");
    exit(0);
}
