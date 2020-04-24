#include "operation.h"
#include <iostream>
#include <stdio.h>
int operation::registered(XMLParse::xml_t *xmltp)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    sprintf(sql,"select * from userbasicinfo where id='%s'",xmltp->child[2]->LabelValue.c_str());
    cout<<xmltp->child[2]->LabelValue.c_str()<<endl;
    res=mysql_query(&conn,sql);
    if(res)
    {
        mysql.closeconn();
        return -1;
    }
    else
    {
        res_ptr = mysql_store_result(&conn);
        if(res_ptr)
        {
            row = mysql_num_rows(res_ptr);
            if(row!=0)
            {
                return -2;
                mysql.closeconn();
            }
        }   
    }
    sprintf(sql,"insert into userbasicinfo(id,pwd,name) values ('%s','%s','%s')",xmltp->child[2]->LabelValue.c_str()
    ,xmltp->child[3]->LabelValue.c_str(),xmltp->child[4]->LabelValue.c_str());
    res=mysql_query(&conn,sql);
    if(res)
    {
        mysql.closeconn();
        return -1;
    }
    else
    {
        mysql.closeconn();
        return 0;
    }
}