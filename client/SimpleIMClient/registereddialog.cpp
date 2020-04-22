#include "registereddialog.h"
#include "ui_registereddialog.h"

registeredDialog::registeredDialog(socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registeredDialog),
    sc(tsc)
{
    ui->setupUi(this);
}

registeredDialog::~registeredDialog()
{
    delete ui;
}

void registeredDialog::on_pushButton_clicked()
{
    if(sc->isconnetion)
    {
        QString sendMessage = ui->lineEdit->text();
        if(!sendMessage.isEmpty())
        {
            sendMessage+='\n';
            sc->TCP_sendMesSocket->write(sendMessage.toUtf8());
        }
        else
            QMessageBox::warning(this,"错误","消息不能为空!",QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器!",QMessageBox::Ok);
}
