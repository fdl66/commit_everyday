/*************************************************************************
	> File Name: deadlock.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月07日 星期四 22时18分53秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
static pthread_t t1;
static pthread_t t2;
static pthread_mutex_t m1;
static pthread_mutex_t m2;
void * print(){
    if(pthread_equal(pthread_self(),t1)){
        pthread_mutex_lock(&m1);
        sleep(1);
        printf("t1 has start and get m1,wait to get m2,loading...................\n");
        sleep(1);
        sleep(1);
        pthread_mutex_lock(&m2);
        printf("t1 has start and get m1,already get m2,ending...................\n");
        pthread_mutex_unlock(&m2);
        pthread_mutex_unlock(&m1);
    }
    if(pthread_equal(pthread_self(),t2)){
        pthread_mutex_lock(&m2);
        sleep(1);
        printf("t2 has start and get m2,wait to get m1,loading...................\n");
        sleep(1);
        sleep(1);
        pthread_mutex_lock(&m1);
        printf("t2 has start and get m2,already get m1,ending...................\n");
        pthread_mutex_unlock(&m1);
        pthread_mutex_unlock(&m2);
    }
    printf("thread id is 0x%x \n",pthread_self());
}
int main(){
    pthread_mutex_init(&m1,NULL);
    pthread_mutex_init(&m2,NULL);
    pthread_create(&t1,NULL,print,NULL);
    pthread_create(&t2,NULL,print,NULL);
    pthread_join(&t1,NULL);
    pthread_join(&t2,NULL);
    return 0;
}
