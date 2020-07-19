#ifndef XMLMANAGE_H
#define XMLMANAGE_H

#include "../public/XMLtool.h"
#include "operation.h"
#include <unistd.h>
#include "Eventloop.h"
class XMLManage
{
    private:
        operation oper;
    public:
        void dataDispose(XMLParse::xml_t *,int *,eventloop *);
        void setdata(XMLParse::xml_t *,int *,eventloop *);
        void setdata(char *,int *,eventloop *);
        void logout(int *);
        int initmysql();
};

#endif