#include "updatadialog.h"
#include "ui_updatadialog.h"
#include "../../public/XMLtool.h"
#include <QMessageBox>

updataDialog::updataDialog(QString Nowid,socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updataDialog),
    sc(tsc),
    id(Nowid)
{
    ui->setupUi(this);
    setWindowTitle("修改个人信息");
    connect(sc->TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
}

updataDialog::~updataDialog()
{
    delete ui;
}

void updataDialog::slot_recvmessage()
{
    QByteArray array;
    array=sc->TCP_sendMesSocket->readAll();
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(array.data());
    xmltp=readparse.get();
    QMessageBox::warning(this,"结果",xmltp->child[1]->LabelValue.c_str(),QMessageBox::Ok);
}

void updataDialog::on_pushButton_clicked()
{
    if(sc->isconnetion)
    {
        QString sendMessage = ui->lineEdit->text();

        if(!sendMessage.isEmpty())
        {
            QString sendMessagexml;
            sendMessagexml+=
                "<?xml version=\"1.0\"?> \
                <iq> \
                <type>set</type> \
                <do>updataname</do> \
                <from>"+id+"</from> \
                <updatainfo>"+sendMessage+"</updatainfo> \
                </iq>";
             sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
        }
        else
            QMessageBox::warning(this,"错误","消息不能为空!",QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器!",QMessageBox::Ok);
}
