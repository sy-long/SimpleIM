#ifndef DATABASE_H
#define DATABASE_H

#include <cstddef>
#include <mysql/mysql.h>

class database
{
    private:
        MYSQL conn;
    public:
        MYSQL* getconn();
        void closeconn();
};

#endif