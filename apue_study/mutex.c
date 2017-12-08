/*************************************************************************
	> File Name: mutex.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月08日 星期五 16时29分37秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<assert.h>
#include<errno.h>


static int option=3;
static pthread_t pthd[5];
static pthread_mutex_t m;
struct timespec* rel_to_abs_time(int seconds){
    static struct timespec tsp;
    int res=clock_gettime(CLOCK_REALTIME,&tsp);
    if(-1==res){
        printf("rel_to_abs_time(%d) error,because %s\n",
                seconds,strerror(errno));
        return NULL;
    }
    tsp.tv_sec+=1;
    return &tsp;
}
void *pth_func(int id){
    switch(option){
        case 0:
            break;
        case 1:
            if(0!=pthread_mutex_lock(&m))
                return -1;
            break;
        case 2:
            if(0!=pthread_mutex_trylock(&m))
                return -1;
            break;
        case 3:
            if(pthread_mutex_timedlock(&m,rel_to_abs_time(1))!=0){
                return -1;
            }
            break;
        default:
            break;
    }
    printf("************thread id: 0x%x ,has started************\n",pthread_self());
    sleep(1);
    if(option!=0){
        pthread_mutex_unlock(&m);
    }
    printf("************thread id: 0x%x ,has end!************\n",pthread_self());
    return id;
}

int main(){
    int res=pthread_mutex_init(&m,NULL);
    assert(res==0);
    for(int i=0;i<5;i++){
        pthread_create(pthd+i,NULL,pth_func,(void *)i);
    }
    int values[5];
    for(int i=0;i<5;i++){
        pthread_join(pthd[i],&values[i]);
    }
    for(int i=0;i<5;i++){
        printf("values[%d]:%d\n",i,values[i]);
    }
    return 0;
}
