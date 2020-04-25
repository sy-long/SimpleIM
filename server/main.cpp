#include <malloc.h>
#include <pthread.h>
#include "makesocket.h"
#include "XMLManage.h"
void attrinit(pthread_attr_t *attrp)
{
    pthread_attr_init(attrp);
    pthread_attr_setdetachstate(attrp,PTHREAD_CREATE_DETACHED);
}
void * handle_call(void * fdptr)
{
    int fd=*(int*)fdptr;
    int num;
    char request[BUFSIZ];
    XMLManage labelmanage;
    while(1)
    {
        num=read(fd,request,BUFSIZ);
        if(num==-1)
            break;
        write(1,request,num);
        labelmanage.dataDispose(request,(int *)fdptr);
    }
}
int main(int ac,char*av[])
{
    int sock,fd;
    pthread_attr_t attr;
    makesocket m;
    int *fdptr;
    pthread_t worker;
    sock=m.createsocket(8888);

    attrinit(&attr);
    while(1)
    {
        fd=accept(sock,NULL,NULL);
        fdptr=(int *)malloc(sizeof(int));
        *fdptr=fd;
        pthread_create(&worker,&attr,handle_call,fdptr);
    }
}