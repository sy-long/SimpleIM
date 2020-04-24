#ifndef XMLMANAGE_H
#define XMLMANAGE_H

#include "../public/XMLtool.h"
#include "operation.h"
#include <unistd.h>
class XMLManage
{
    private:
        operation oper;
    public:
        void dataDispose(char *,int *);
};

#endif