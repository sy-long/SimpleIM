#include <iostream>
#include <malloc.h>
#include <pthread.h>
#include "makesocket.h"
#include "../public/XMLtool.h"
void attrinit(pthread_attr_t *attrp)
{
    pthread_attr_init(attrp);
    pthread_attr_setdetachstate(attrp,PTHREAD_CREATE_DETACHED);
}
void * handle_call(void * fdptr)
{
    int fd=*(int*)fdptr;
    int num;
    XMLParse readparse;
    XMLParse::xml_t *p;
    char request[BUFSIZ];
    while(1){
        num=read(fd,request,BUFSIZ);
        if(num==0)
            break;
        readparse.parse(request);
        p=readparse.get();
        cout<<readparse.getv()<<endl;
        cout<<p->LabelName<<endl;
        cout<<p->LabelValue<<endl;
        cout<<p->child.size()<<endl;
        if(p->child.size()!=0){
            for(int i=0;i<p->child.size();i++){
                cout<<p->child[i]->LabelName<<endl;
                cout<<p->child[i]->LabelValue<<endl;
            }
        }
        //write(1,request,num);
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