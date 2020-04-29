#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QString Nowid,socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDialog),
    sc(tsc),
    id(Nowid)
{
    ui->setupUi(this);
}

chatDialog::~chatDialog()
{
    delete ui;
}


void chatDialog::sent_message(QString uid)
{
    QString text=ui->textEdit_2->toPlainText();
    ui->textEdit_2->clear();
    QString local_text="Me:"+text;
    ui->textEdit->append(local_text);
    QString sendMessagexml;
    sendMessagexml+=
        "<?xml version=\"1.0\"?> \
        <message> \
        <type>personal</type> \
        <state>sendm</state> \
        <from>"+id+"</from> \
        <to>"+uid+"</to> \
        <text>"+text+"</text> \
        </iq>";
     sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
}

void chatDialog::get_message(QString uname,QString text)
{
    QString local_text=uname+":"+text;
    ui->textEdit->append(local_text);
}
