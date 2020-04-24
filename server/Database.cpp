#include "Database.h"

MYSQL* database::getconn()
{
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","123456","SimpleIM",0,NULL,CLIENT_FOUND_ROWS))
        return &conn;
    else
        return NULL;
}

void database::closeconn()
{
    mysql_close(&conn);
}