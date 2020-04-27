#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include "../public/XMLtool.h"
#include <pthread.h>
#include <vector>
class eventloop
{   
    public:
        struct pxmlinfo
            {
                XMLParse::xml_t info;
                long pid;
                int sockfd;
            };
    private:
        pthread_mutex_t lock;
        vector<pxmlinfo> pxmlarr;
    public:
        eventloop();
        int sendarr(XMLParse::xml_t,long,int);
        int getarr(pxmlinfo *,long);
};

#endif