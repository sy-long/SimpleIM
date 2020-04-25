#ifndef OPERATION_H
#define OPERATION_H
#include "../public/XMLtool.h"
#include "Database.h"
class operation{
    public:
        int registered(XMLParse::xml_t *);
        int login(XMLParse::xml_t *);
        int logout(XMLParse::xml_t *);
};

#endif