#include "operation.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

operation::operation():id(""),state(0){}
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
        sprintf(sql,"insert into online(id,state,pid,sockfd) values ('%s','%d','%ld','%d')",xmltp->child[2]->LabelValue.c_str()
        ,0,0,0);
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
int operation::login(XMLParse::xml_t *xmltp,eventloop *loop,int fd)
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
                        id=xmltp->child[1]->LabelValue;
                        state=1;
                        sprintf(sql,"update online set pid = replace(pid,0,'%ld') where id like '%s'",pthread_self(),xmltp->child[1]->LabelValue.c_str());
                        res=mysql_query(&conn,sql);
                        if(res)
                        {
                            mysql.closeconn();
                            return -1;
                        }
                        else
                        {
                            sprintf(sql,"update online set sockfd = replace(sockfd,0,'%d') where id like '%s'",fd,xmltp->child[1]->LabelValue.c_str());
                            res=mysql_query(&conn,sql);
                            if(res)
                            {
                                mysql.closeconn();
                                return -1;
                            }
                            else
                            {
                                id=xmltp->child[1]->LabelValue;
                                state=1;
                                mysql.closeconn();
                                return 0;
                            }  
                        }
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
int operation::logout(int fd)
{
    if(state==1)
    {
        database mysql;
        MYSQL conn=*(mysql.getconn());
        int res;
        char sql[100];
        sprintf(sql,"update online set state = replace(state,1,0) where id like '%s'",id.c_str());
        res=mysql_query(&conn,sql);
        if(res)
        {
            mysql.closeconn();
            return -1;
        }
        else
        {
            sprintf(sql,"update online set pid = replace(pid,%ld,0) where id like '%s'",pthread_self(),id.c_str());
            res=mysql_query(&conn,sql);
            if(res)
            {
                mysql.closeconn();
                return -1;
            }
            else
            {
                sprintf(sql,"update online set sockfd = replace(sockfd,%d,0) where id like '%s'",fd,id.c_str());
                res=mysql_query(&conn,sql);
            }
        }
    }
    else
        return -2;
}

int operation::addfriend(XMLParse::xml_t *xmltp,eventloop *loop)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    MYSQL_ROW result_row;
    if(xmltp->child[2]->LabelValue=="untreated")
    {
        sprintf(sql,"select * from online where id='%s'",xmltp->child[4]->LabelValue.c_str());
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
                    if(!strcmp(result_row[1],"1"))
                    {
                        xmltp->child[2]->LabelValue="processed";
                        loop->sendarr(*xmltp,atol(result_row[2]),atoi(result_row[3]));
                        pthread_kill(atol(result_row[2]),SIGUSR1);
                        mysql.closeconn();
                        return 0;
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
    else if(xmltp->child[2]->LabelValue=="processed")
    {
        mysql.closeconn();
        return 1;
    }
    else if(xmltp->child[2]->LabelValue=="accept")
    {
        sprintf(sql,"insert into friends(id1,id2) values ('%s','%s')",xmltp->child[3]->LabelValue.c_str()
        ,xmltp->child[4]->LabelValue.c_str());
        res=mysql_query(&conn,sql);
        if(res)
        {
            mysql.closeconn();
            return -1;
        }
        else
        {
            sprintf(sql,"select * from online where id='%s'",xmltp->child[4]->LabelValue.c_str());
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
                        if(!strcmp(result_row[1],"1"))
                        {
                            xmltp->child[2]->LabelValue="accepted";
                            loop->sendarr(*xmltp,atol(result_row[2]),atoi(result_row[3]));
                            pthread_kill(atol(result_row[2]),SIGUSR1);
                            mysql.closeconn();
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
    }
    else if(xmltp->child[2]->LabelValue=="accepted")
    {
        mysql.closeconn();
        return 2;
    }
}

int operation::getfriendlist(XMLParse::xml_t *xmltp,vector<string> *list)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    MYSQL_ROW result_row;
    sprintf(sql,"select * from friends where id1='%s'",xmltp->child[2]->LabelValue.c_str());
    res=mysql_query(&conn,sql);
    cout<<"1"<<endl;
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
                result_row=mysql_fetch_row(res_ptr);
                while(result_row!=NULL)
                {
                    list->push_back(result_row[1]);
                    result_row=mysql_fetch_row(res_ptr);
                }
            }
        }
        sprintf(sql,"select * from friends where id2='%s'",xmltp->child[2]->LabelValue.c_str());
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
                    result_row=mysql_fetch_row(res_ptr);
                    while(result_row!=NULL)
                    {
                        list->push_back(result_row[0]);
                        result_row=mysql_fetch_row(res_ptr);
                    }
                }
            }
            mysql.closeconn();
            return 0;
        }
    }
}

int operation::communication(XMLParse::xml_t *xmltp,eventloop *loop)
{
    database mysql;
    MYSQL conn=*(mysql.getconn());
    int res;
    char sql[100];
    MYSQL_RES *res_ptr;
    int row;
    MYSQL_ROW result_row;
    if(xmltp->child[1]->LabelValue=="sendm")
    {
        cout<<"deal"<<endl;
        sprintf(sql,"select * from online where id='%s'",xmltp->child[3]->LabelValue.c_str());
        res=mysql_query(&conn,sql);
        cout<<xmltp->child[1]->LabelValue<<endl;
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
                    if(!strcmp(result_row[1],"1"))
                    {
                        cout<<"to kill"<<endl;
                        xmltp->child[1]->LabelValue="getm";
                        loop->sendarr(*xmltp,atol(result_row[2]),atoi(result_row[3]));
                        pthread_kill(atol(result_row[2]),SIGUSR1);
                        mysql.closeconn();
                        return 0;
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
    else if(xmltp->child[1]->LabelValue=="getm")
    {
        cout<<"getm"<<endl;
        mysql.closeconn();
        return 1;
    }
}