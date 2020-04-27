#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include "../../public/XMLtool.h"
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
    qDebug()<<"ok"<<endl;
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
                QString info=xmltp->child[2]->LabelValue.c_str();
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
                        </iq>";
                     sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
                }
            }
            if(xmltp->child[1]->LabelValue=="添加成功")
            {
                QMessageBox::warning(this,"好友请求",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
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
