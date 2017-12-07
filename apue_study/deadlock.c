/*************************************************************************
	> File Name: deadlock.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月07日 星期四 22时18分53秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
void * print(){
    printf("thread id is 0x%x \n",pthread_self());
}
int main(){
    pthread_mutex_t m1;
    pthread_mutex_t m2;
    pthread_mutex_init(m1,NULL);
    pthread_mutex_init(m2,NULL);
    return 0;
}
