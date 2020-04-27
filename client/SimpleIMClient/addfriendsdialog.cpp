#include "addfriendsdialog.h"
#include "ui_addfriendsdialog.h"
#include "../../public/XMLtool.h"
#include <QMessageBox>
AddfriendsDialog::AddfriendsDialog(QString Nowid,socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddfriendsDialog),
    sc(tsc),
    id(Nowid)
{
    ui->setupUi(this);
    setWindowTitle("添加好友");
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
}

AddfriendsDialog::~AddfriendsDialog()
{
    delete ui;
}

void AddfriendsDialog::slot_recvmessage()
{
    QByteArray array;
    array=sc->TCP_sendMesSocket->readAll();
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(array.data());
    xmltp=readparse.get();
    QMessageBox::warning(this,"结果",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
    close();
}

void AddfriendsDialog::on_pushButton_clicked()
{
    qDebug()<<"ok"<<endl;
    if(sc->isconnetion)
    {
        QString sendMessage = ui->lineEdit->text();

        if(!sendMessage.isEmpty())
        {
            if(!(id==sendMessage))
            {
                QString sendMessagexml;
                sendMessagexml+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <do>addfriends</do> \
                    <state>untreated</state> \
                    <from>"+id+"</from> \
                    <to>"+sendMessage+"</to> \
                    </iq>";
                 sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
            }
            else
            {
                QMessageBox::warning(this,"错误","不能添加自身!",QMessageBox::Ok);
            }
        }
        else
            QMessageBox::warning(this,"错误","消息不能为空!",QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器!",QMessageBox::Ok);
}
