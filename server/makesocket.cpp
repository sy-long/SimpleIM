#include "makesocket.h"

int makesocket::createsocket(int portnum){
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id;

    sock_id=socket(PF_INET,SOCK_STREAM,0);
    if(sock_id==-1)
        return -1;
    bzero((void*)&saddr,sizeof(saddr));
    //gethostname(hostname,HOSTLEN);
    //hp=gethostbyname(hostname);
    //bcopy((void *)hp->h_addr,(void *)&saddr.sin_addr,hp->h_length);
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    saddr.sin_port=htons(portnum);
    saddr.sin_family=AF_INET;
    if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr))!=0)
        return -1;
    if(listen(sock_id,BACKLOG)!=0)
        return -1;
    return sock_id;
}