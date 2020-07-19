#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <iostream>
#include "makesocket.h"
#include "XMLManage.h"
#include "Eventloop.h"
#include "../public/XMLtool.h"

eventloop *loop=new eventloop;
void wakeup(int signum)
{
    int ret;
    eventloop::pxmlinfo tpxminfo;
    ret=loop->getarr(&tpxminfo,pthread_self());
    if(ret!=0)
    {
        XMLManage labelmanage;
        labelmanage.setdata(&tpxminfo.info,&tpxminfo.sockfd,loop);
        cout<<tpxminfo.info.child[2]->LabelValue<<":"<<tpxminfo.sockfd<<endl;
    }
}
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
    signal(SIGUSR1,wakeup);
    while(1)
    {
        num=read(fd,request,BUFSIZ);
        if(num==0)
        {
            break;
        }
        labelmanage.setdata(request,(int *)fdptr,loop);
    }
    labelmanage.logout((int *)fdptr);
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
    XMLManage *tManage = new XMLManage;
    tManage->initmysql();
    while(1)
    {
        fd=accept(sock,NULL,NULL);
        fdptr=(int *)malloc(sizeof(int));
        *fdptr=fd;
        pthread_create(&worker,&attr,handle_call,fdptr);
    }
}