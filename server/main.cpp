#include "makesocket.h"
#include <stdio.h>
int main(int ac,char*av[])
{
    int sock,fd;
    FILE* fpin;
    char request[BUFSIZ];
    makesocket m;
    sock=m.createsocket(8888);
    while(1)
    {
        fd=accept(sock,NULL,NULL);
        fpin=fdopen(fd,"r");
        fgets(request,BUFSIZ,fpin);
        printf("got a call:request=%s\n",request);
        fclose(fpin);
    }
}