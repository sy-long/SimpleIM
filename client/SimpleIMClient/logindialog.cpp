#include "login.h"
#include "ui_logindialog.h"
#include "../../public/XMLtool.h"
#include "maindialog.h"
loginDialog::loginDialog(socketConnect *tsc,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
    , sc(tsc)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆");
    sc->isconnetion=false;
    sc->TCP_sendMesSocket=new QTcpSocket();
    sc->TCP_sendMesSocket->abort();
    sc->TCP_sendMesSocket->connectToHost("39.108.100.247",8888);
    connect(sc->TCP_sendMesSocket,SIGNAL(connected()),this,SLOT(slot_connected()));
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::slot_recvmessage()
{
    QByteArray array;
    array=sc->TCP_sendMesSocket->readAll();
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(array.data());
    xmltp=readparse.get();
    if(xmltp->child[1]->LabelValue!="登陆成功")
        QMessageBox::warning(this,"结果",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
    if(xmltp->child[1]->LabelValue=="登陆成功")
    {
        this->close();
        disconnect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
        MainDialog *maindialog=new MainDialog(ui->lineEdit->text(),sc,this);
        maindialog->show();
    }
}

void loginDialog::on_pushButton_2_clicked()
{
    if(sc->isconnetion)
    {
        QString sendMessage = ui->lineEdit->text();
        QString sendMessage1 = ui->lineEdit_2->text();

        if(!sendMessage.isEmpty()&&!sendMessage1.isEmpty())
        {

                QString sendMessagexml;
                sendMessagexml+=
                    "<?xml version=\"1.0\"?> \
                    <presence> \
                    <type>login</type> \
                    <uid>"+sendMessage+"</uid> \
                    <upwd>"+sendMessage1+"</upwd> \
                    </presence>";
                 sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
        }
        else
            QMessageBox::warning(this,"错误","消息不能为空!",QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器!",QMessageBox::Ok);
}

void loginDialog::on_pushButton_clicked()
{
    disconnect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
    registeredDialog registeredDialog(sc,this);
    registeredDialog.exec();
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
}

void loginDialog::slot_connected()
{
    sc->isconnetion = true;
}

