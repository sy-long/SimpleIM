#include "operation.h"
#include <stdio.h>
#include <string.h>
int operation::registered(XMLParse::xml_t *xmltp)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    sprintf(sql,"select * from userbasicinfo where id='%s'",xmltp->child[2]->LabelValue.c_str());
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
                mysql.closeconn();
                return -2;
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
        sprintf(sql,"insert into online(id,state) values ('%s','%d')",xmltp->child[2]->LabelValue.c_str()
        ,0);
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
}
int operation::login(XMLParse::xml_t *xmltp)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    MYSQL_ROW result_row;
    sprintf(sql,"select * from userbasicinfo where id='%s'",xmltp->child[1]->LabelValue.c_str());
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
            if(row==0)
            {
                mysql.closeconn();
                return -2;
            }
            else
            {
                result_row=mysql_fetch_row(res_ptr);
                if(!strcmp(result_row[2],xmltp->child[2]->LabelValue.c_str()))
                {
                    sprintf(sql,"update online set state = replace(state,0,1) where id like '%s'",xmltp->child[1]->LabelValue.c_str());
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
                else
                {
                    mysql.closeconn();
                    return -3;
                }
            }
            
        }   
    }
}
int operation::logout(XMLParse::xml_t *xmltp)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    MYSQL_ROW result_row;
    sprintf(sql,"update online set state = replace(state,1,0) where id like '%s'",xmltp->child[1]->LabelValue.c_str());
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