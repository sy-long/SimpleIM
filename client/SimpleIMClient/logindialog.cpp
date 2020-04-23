#include "login.h"
#include "ui_logindialog.h"

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
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_2_clicked()
{

}

void loginDialog::on_pushButton_clicked()
{
    registeredDialog registeredDialog(sc,this);
    registeredDialog.exec();
}

void loginDialog::slot_connected()
{
    sc->isconnetion = true;
}

