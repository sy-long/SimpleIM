#include "Eventloop.h"

eventloop::eventloop()
{
    pthread_mutex_init(&lock,NULL);
}

int eventloop::sendarr(XMLParse::xml_t xml,long pid,int sockfd)
{
    pxmlinfo tpxmlinfo;
    tpxmlinfo.info=xml;
    tpxmlinfo.pid=pid;
    tpxmlinfo.sockfd=sockfd;
    pthread_mutex_lock(&lock);
    pxmlarr.push_back(tpxmlinfo);
    pthread_mutex_unlock(&lock);
    return 1;
}

int eventloop::getarr(pxmlinfo *pxm,long pid)
{   
    int state=0;
    pthread_mutex_lock(&lock);
    for(vector<pxmlinfo>::iterator it=pxmlarr.begin();it!=pxmlarr.end();++it)
    {
        
        if((*it).pid==pid)
        {
            state=1;
            *pxm=(*it);
            pxmlarr.erase(it);
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    return state;
}