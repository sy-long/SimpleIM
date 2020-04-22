//makesocket.h
#ifndef MAKESOCKET_H
#define MAKESOCKET_H
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#define HOSTLEN 256
#define BACKLOG 1

class makesocket
{
public:
    int createsocket(int);
};

#endif