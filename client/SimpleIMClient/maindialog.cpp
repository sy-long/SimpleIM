#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <stdlib.h>
#include "../../public/XMLtool.h"
#include "chathellodialog.h"
#include <vector>

struct Contact_window_info
{
    int listitemindex;
    int stackitemindex;
    string uid;
    string uname;
};
vector<Contact_window_info> contact_table;
MainDialog::MainDialog(QString Nowid,socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    sc(tsc),
    id(Nowid)
{
    ui->setupUi(this);
    setWindowTitle("SimpleIM");
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
    initfriendlist();
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(on_listWidget_clicked()));
    ui->stackedWidget->addWidget(new ChatHelloDialog);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainDialog::on_listWidget_clicked()
{
    static int count=0;
    int row=ui->listWidget->currentRow();
    Contact_window_info tinfo;
    for(int i=0;i<contact_table.size();i++)
    {
        if(row==contact_table[i].listitemindex)
        {
            tinfo=contact_table[i];
            break;
        }
    }
    static int lastindex;
    if(count!=0)
    {
        ui->listWidget->item(lastindex)->setBackgroundColor("white");
    }
    lastindex=ui->listWidget->currentRow();
    ui->stackedWidget->setCurrentIndex(tinfo.stackitemindex);
    ui->label_2->setText(tinfo.uname.c_str());
    ui->listWidget->currentItem()->setBackgroundColor("gray");
    count++;
}

void MainDialog::initfriendlist()
{
            QString sendMessagexml;
            sendMessagexml+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>get</type> \
                <do>friendslist</do> \
                <uid>"+id+"</uid> \
                </iq>";
             sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::slot_recvmessage()
{
    QByteArray array;
    array=sc->TCP_sendMesSocket->readAll();
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(array.data());
    xmltp=readparse.get();
    if(xmltp->LabelName=="iq")
    {
        if(xmltp->child[0]->LabelValue=="set")
        {
            if(xmltp->child[1]->LabelValue=="好友添加请求")
            {
                QString info=xmltp->child[3]->LabelValue.c_str();
                info+="用户想添加您为好友，是否添加？";
                int ret;
                ret=QMessageBox::warning(this,"好友请求",info,QMessageBox::Ok,QMessageBox::No);
                if(ret==QMessageBox::Ok)
                {
                    QString sendMessagexml;
                    sendMessagexml+=
                        "<?xml version=\"1.0\"?> \
                        <iq> \
                        <type>set</type> \
                        <do>addfriends</do> \
                        <state>accept</state> \
                        <from>"+id+"</from> \
                        <to>"+xmltp->child[2]->LabelValue.c_str()+"</to> \
                        <toname>"+xmltp->child[3]->LabelValue.c_str()+"</toname> \
                        </iq>";
                     sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
                     Contact_window_info tinfo;
                     int nowlistitemnum=ui->listWidget->count();
                     ui->listWidget->insertItem(nowlistitemnum,xmltp->child[3]->LabelValue.c_str());
                     chatDialog *ptr;
                     ptr=new chatDialog(id,sc);
                     int nowstackwitemnum=ui->stackedWidget->count();
                     ui->stackedWidget->addWidget(ptr);
                     tinfo.listitemindex=nowlistitemnum;
                     tinfo.stackitemindex=nowstackwitemnum;
                     tinfo.uid=xmltp->child[2]->LabelValue;
                     tinfo.uname=xmltp->child[3]->LabelValue;
                     contact_table.push_back(tinfo);
                }
            }
            if(xmltp->child[1]->LabelValue=="添加成功")
            {
                QMessageBox::warning(this,"通知",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
                Contact_window_info tinfo;
                int nowlistitemnum=ui->listWidget->count();
                ui->listWidget->insertItem(nowlistitemnum,xmltp->child[3]->LabelValue.c_str());
                chatDialog *ptr;
                ptr=new chatDialog(id,sc);
                int nowstackwitemnum=ui->stackedWidget->count();
                ui->stackedWidget->addWidget(ptr);
                tinfo.listitemindex=nowlistitemnum;
                tinfo.stackitemindex=nowstackwitemnum;
                tinfo.uid=xmltp->child[2]->LabelValue;
                tinfo.uname=xmltp->child[3]->LabelValue;
                contact_table.push_back(tinfo);
            }
            if(xmltp->child[1]->LabelValue=="删除成功!")
            {
                QMessageBox::warning(this,"通知",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
                int index=ui->listWidget->currentRow();
                ui->listWidget->takeItem(index);
            }
            if(xmltp->child[1]->LabelValue=="好友删除通知")
            {
                QMessageBox::warning(this,"通知",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
                int index;
                Contact_window_info tinfo;
                for(int i=0;i<contact_table.size();i++)
                {
                    if(xmltp->child[2]->LabelValue==contact_table[i].uid)
                    {
                        tinfo=contact_table[i];
                        break;
                    }
                }
                index=tinfo.listitemindex;
                ui->listWidget->takeItem(index);
            }
        }
        if(xmltp->child[0]->LabelValue=="result")
        {
            if(xmltp->child[1]->LabelValue=="拉取好友列表失败，数据库错误")
            {
                QMessageBox::warning(this,"好友请求",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok,QMessageBox::No);
            }
            if(xmltp->child[1]->LabelValue=="拉取成功")
            {
                chatDialog *ptr;
                int index=2;
                for(int i=2;i<xmltp->child.size();i+=2)
                {
                    Contact_window_info tinfo;
                    ui->listWidget->insertItem(index-2,xmltp->child[i+1]->LabelValue.c_str());
                    ptr=new chatDialog(id,sc);
                    ui->stackedWidget->addWidget(ptr);
                    tinfo.listitemindex=index-2;
                    tinfo.stackitemindex=index+1;
                    tinfo.uid=xmltp->child[i]->LabelValue;
                    tinfo.uname=xmltp->child[i+1]->LabelValue;
                    contact_table.push_back(tinfo);
                    index++;
                }
            }
        }
    }
    if(xmltp->LabelName=="message")
    {
        if(xmltp->child[0]->LabelValue=="result")
        {
            QMessageBox::warning(this,"结果",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
        }
        else if(xmltp->child[0]->LabelValue=="getm")
        {
            string uid = xmltp->child[1]->LabelValue;
            Contact_window_info tinfo;
            for(int i=0;i<contact_table.size();i++)
            {
                if(uid==contact_table[i].uid)
                {
                    tinfo=contact_table[i];
                    break;
                }
            }
            chatDialog *NowPage;
            NowPage=(chatDialog *)ui->stackedWidget->widget(tinfo.stackitemindex);
            NowPage->get_message(QString::fromStdString(tinfo.uname),QString::fromStdString(xmltp->child[3]->LabelValue));
            int nowlistindex=ui->listWidget->currentRow();
            if(nowlistindex!=tinfo.listitemindex)
            {
                ui->listWidget->item(tinfo.listitemindex)->setBackgroundColor("skyblue");
            }
        }
    }
}

void MainDialog::closeEvent(QCloseEvent *e)
{
    if( QMessageBox::question(this,tr("退出"),tr("你确定要退出SimpleIM吗？"),QMessageBox::Yes, QMessageBox::No )== QMessageBox::Yes)
    {
        e->accept();
    }
    else
        e->ignore();
}

void MainDialog::on_pushButton_clicked()
{
    disconnect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
    AddfriendsDialog addfriendsDialog(id,sc,this);
    addfriendsDialog.exec();
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
}

void MainDialog::on_pushButton_2_clicked()
{
    chatDialog *NowPage;
    NowPage=(chatDialog *)ui->stackedWidget->currentWidget();
    int index=ui->stackedWidget->currentIndex();
    Contact_window_info tinfo;
    for(int i=0;i<contact_table.size();i++)
    {
        if(index==contact_table[i].stackitemindex)
        {
            tinfo=contact_table[i];
            break;
        }
    }
    NowPage->sent_message(QString::fromStdString(tinfo.uid));
}

void MainDialog::on_pushButton_3_clicked()
{
    if(sc->isconnetion)
    {
        int index=ui->listWidget->currentRow();
        Contact_window_info tinfo;
        for(int i=0;i<contact_table.size();i++)
        {
            if(index==contact_table[i].listitemindex)
            {
                tinfo=contact_table[i];
                break;
            }
        }
        QString sendMessagexml;
        sendMessagexml+=
            "<?xml version=\"1.0\"?> \
            <iq> \
            <type>set</type> \
            <do>delfriends</do> \
            <state>untreated</state> \
            <from>"+id+"</from> \
            <to>"+QString::fromStdString(tinfo.uid)+"</to> \
            </iq>";
         sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
    }
}
