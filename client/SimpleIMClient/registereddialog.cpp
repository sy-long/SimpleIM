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
        QString sendMessage1 = ui->lineEdit_2->text();
        QString sendMessage2 = ui->lineEdit_3->text();
        QString sendMessage3 = ui->lineEdit_4->text();

        if(!sendMessage.isEmpty()&&!sendMessage1.isEmpty()&&!sendMessage2.isEmpty()&&!sendMessage3.isEmpty())
        {
            if(!(sendMessage1!=sendMessage2))
            {
                sendMessage+='\n';
                sc->TCP_sendMesSocket->write(sendMessage.toUtf8());
                sendMessage1+='\n';
                sc->TCP_sendMesSocket->write(sendMessage.toUtf8());
                sendMessage2+='\n';
                sc->TCP_sendMesSocket->write(sendMessage.toUtf8());
                sendMessage3+='\n';
                sc->TCP_sendMesSocket->write(sendMessage.toUtf8());
            }
            else
                QMessageBox::warning(this,"错误","两次密码不一致!",QMessageBox::Ok);
        }
        else
            QMessageBox::warning(this,"错误","消息不能为空!",QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this,"错误","未连接到服务器!",QMessageBox::Ok);
}
