#include "XMLManage.h"
#include <string>
#include <iostream>
#include <vector>
void XMLManage::setdata(XMLParse::xml_t *xmltp,int *fdptr,eventloop *loop)
{
    dataDispose(xmltp,fdptr,loop);
}
void XMLManage::setdata(char *data,int *fdptr,eventloop *loop)
{
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(data);
    xmltp=readparse.get();
    dataDispose(xmltp,fdptr,loop);
}
void XMLManage::dataDispose(XMLParse::xml_t *xmltp,int *fdptr,eventloop *loop)
 {
    
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
            else if(xmltp->child[1]->LabelValue=="addfriends")
            {
                ret=oper.addfriend(xmltp,loop);
                if(ret==-1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>添加失败，数据库错误</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==-2)
                {
                    
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>添加失败，没有该用户</item> \
                    </iq>";
                    
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==-3)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>添加失败，该用户不在线</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==0)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>添加成功,等待对方同意</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <item>好友添加请求</item> \
                    <from>"+xmltp->child[3]->LabelValue+"</from> \
                    <fromname>"+xmltp->child[4]->LabelValue+"</fromname> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==2)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <item>添加成功</item> \
                    <from>"+xmltp->child[3]->LabelValue+"</from> \
                    <fromname>"+xmltp->child[5]->LabelValue+"</fromname> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
            }
            else if(xmltp->child[1]->LabelValue=="delfriends")
            {
                ret=oper.delfriend(xmltp,loop);
                if(ret==-1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>删除失败，数据库错误</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==-2)
                {
                    
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>删除失败，没有该用户</item> \
                    </iq>";
                    
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==-3)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>删除失败，该用户不在线</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==0)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <item>删除成功!</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <item>好友删除通知</item> \
                    <from>"+xmltp->child[3]->LabelValue+"</from> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
            }
        }
        if(xmltp->child[0]->LabelValue=="get")
        {
            if(xmltp->child[1]->LabelValue=="friendslist")
            {
                vector<operation::friendlistinfo> list;
                ret=oper.getfriendlist(xmltp,&list);
                if(ret==-1)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>拉取好友列表失败，数据库错误</item> \
                    </iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
                else if(ret==0)
                {
                    sendbuf+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>result</type> \
                    <item>拉取成功</item>     ";
                    for(int i=0;i<list.size();i++)
                    {
                        sendbuf+="<item>"+list[i].uid+"</item>     ";
                        sendbuf+="<item>"+list[i].name+"</item>     ";
                    }
                    sendbuf+="</iq>";
                    write(fd,sendbuf.c_str(),sendbuf.size());
                }
            }
        }
    }
    if(xmltp->LabelName=="presence")
    {
        if(xmltp->child[0]->LabelValue=="login")
        {
            ret=oper.login(xmltp,loop,fd);
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
                <item>登陆失败，没有此账号</item> \
                </iq>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==-3)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>result</type> \
                <item>登陆失败，密码错误</item> \
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
    }
    if(xmltp->LabelName=="message")
    {
        if(xmltp->child[0]->LabelValue=="personal")
        {
            cout<<"manage"<<endl;
            ret=oper.communication(xmltp,loop);
            if(ret==-1)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <message> \
                <type>result</type> \
                <item>发送失败，数据库错误</item> \
                </message>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==-2)
            {
                
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <message> \
                <type>result</type> \
                <item>发送失败，没有该用户</item> \
                </message>";
                
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==-3)
            {
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <message> \
                <type>result</type> \
                <item>发送失败，该用户不在线</item> \
                </message>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
            else if(ret==1)
            {
                cout<<"message get"<<endl;
                sendbuf+=
                "<?xml version=\"1.0\"?> \
                <message> \
                <type>getm</type> \
                <from>"+xmltp->child[2]->LabelValue+"</from> \
                <to>"+xmltp->child[3]->LabelValue+"</to> \
                <text>"+xmltp->child[4]->LabelValue+"</text> \
                </message>";
                write(fd,sendbuf.c_str(),sendbuf.size());
            }
        }
    }
 }

 void XMLManage::logout(int *fdptr)
 {
     int fd=*(fdptr);
     oper.logout(fd);
 }