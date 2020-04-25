#include "XMLManage.h"
#include <string>
#include <iostream>
 void XMLManage::dataDispose(char *data,int *fdptr)
 {
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(data);
    xmltp=readparse.get();
    int ret;
    int fd=*(fdptr);
    string sendbuf;
    if(xmltp->LabelName=="iq")
    {
        if(xmltp->child[0]->LabelValue=="set")
        {
            if(xmltp->child[1]->LabelValue=="registered")
            {
                ret=oper.registered(xmltp);
                if(ret==-1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>注册失败，数据库错误</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==-2)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>注册失败，已有此账号</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>注册成功</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
            }
        }
    }
    if(xmltp->LabelName=="presence")
    {
        if(xmltp->child[0]->LabelValue=="login")
        {
            ret=oper.login(xmltp);
            if(ret==-1)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>result</type> \
                <item>登陆失败，数据库错误</item> \
                </iq>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==-2)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>result</type> \
                <item>注册失败，没有此账号</item> \
                </iq>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==-3)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>result</type> \
                <item>注册失败，密码错误</item> \
                </iq>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>result</type> \
                <item>登陆成功</item> \
                </iq>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
        }
        else if(xmltp->child[0]->LabelValue=="logout")
        {
            ret=oper.logout(xmltp);
        }
    }
 }