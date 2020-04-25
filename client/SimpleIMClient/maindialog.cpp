#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <windows.h>
MainDialog::MainDialog(QString Nowid,socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    sc(tsc),
    id(Nowid)
{
    ui->setupUi(this);
    setWindowTitle("SimpleIM");
}

MainDialog::~MainDialog()
{
    qDebug()<<sc->isconnetion;
    if(sc->isconnetion)
    {
        QString sendMessagexml;
        sendMessagexml+=
        "<?xml version=\"1.0\"?> \
        <presence> \
        <type>logout</type> \
        <uid>"+id+"</uid> \
        </presence>";
        sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
        Sleep(5000);
    }
    qDebug()<<sc->isconnetion;
    delete ui;
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
