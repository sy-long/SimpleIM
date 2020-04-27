#ifndef OPERATION_H
#define OPERATION_H
#include "../public/XMLtool.h"
#include "Database.h"
#include "Eventloop.h"
class operation{
    private:
        string id;
        int state;
    public:
        operation();
        int registered(XMLParse::xml_t *);
        int login(XMLParse::xml_t *,eventloop *,int);
        int logout(int);
        int addfriend(XMLParse::xml_t *,eventloop *);
        int getfriendlist(XMLParse::xml_t *);
};

#endif