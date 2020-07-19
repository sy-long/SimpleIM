#ifndef OPERATION_H
#define OPERATION_H
#include "../public/XMLtool.h"
#include "Database.h"
#include "Eventloop.h"
#include <vector>
class operation{
    private:
        string id;
        int state;
    public:
        struct friendlistinfo
        {
            string uid;
            string name;
        };
    public:
        operation();
        int registered(XMLParse::xml_t *);
        int login(XMLParse::xml_t *,eventloop *,int);
        int logout(int);
        int addfriend(XMLParse::xml_t *,eventloop *);
        int getfriendlist(XMLParse::xml_t *,vector<friendlistinfo> *);
        int communication(XMLParse::xml_t *,eventloop *);
        int delfriend(XMLParse::xml_t *,eventloop *);
        int updataname(XMLParse::xml_t *);
        int initmysql();
};

#endif