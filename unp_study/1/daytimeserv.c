/*************************************************************************
	> File Name: daytimeserv.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月14日 星期四 20时32分01秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define MAXLINE 1024
int
Socket(int family,int type,int protocol){
    int n;
    if((n=socket(family,type,protocol))<0){
        printf("connect error %s errno %d\n",strerror(n),n);
        exit(n);
    }
    return n;
}
int main(){
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,1024);
    for(;;){
        connfd = accept(listenfd,(struct sockaddr *)NULL,NULL);
        ticks = time(NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        write(connfd,buff,strlen(buff));
        close(connfd);
    }

}
