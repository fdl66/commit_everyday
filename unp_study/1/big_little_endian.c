#include<stdio.h>
#include<sys/utsname.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    union{
        short t;
        char s[sizeof(short)];
    }un;
    un.t=0x0102;
    char hostname[256];
    struct utsname uts;
    if(gethostname(hostname,255)!=0||uname(&uts)<0){
        fprintf(stderr,"Could not get host information\n");
        exit(1);
    }
    printf("hostname:%s\n",hostname);
    printf("System is %s on %s hardware\n",uts.sysname,uts.machine);
    printf("Nodename is %s\n",uts.nodename);
    printf("Version is %s,%s\n",uts.release,uts.version);
    if(sizeof(short)==2){
        if(un.s[0]==2&&un.s[1]==1){
            printf("little-endian!\n");
        }else if(un.s[0]==1&&un.s[1]==2){
            printf("big-endian!\n");
        }else {
            printf("Unknown !\n");
        }
    }else{
        printf("sizeof(short)=%d\n",sizeof(short));
    }
    exit(0);
}
