#include "makesocket.h"
#define BUFSIZ 4096
int main(int ac,char*av[])
{
    int sock,fd;
    char request[BUFSIZ];
    makesocket m;
    sock=m.createsocket(8888);
    fd=accept(sock,NULL,NULL);
    int num;
    while(1)
    {
        num=read(fd,request,BUFSIZ);
        write(1,request,num);
    }
}