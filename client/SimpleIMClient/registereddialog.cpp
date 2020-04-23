#include "registereddialog.h"
#include "ui_registereddialog.h"

registeredDialog::registeredDialog(socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registeredDialog),
    sc(tsc)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
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

                QString sendMessagexml;
                sendMessagexml+=
                    "<?xml version=\"1.0\"?> \
                    <iq> \
                    <type>set</type> \
                    <do>registered</do> \
                    <uid>"+sendMessage+"</uid> \
                    <upwd>"+sendMessage1+"</upwd> \
                    <uname>"+sendMessage3+"</upwd> \
                    </iq>";
                 sc->TCP_sendMesSocket->write(sendMessagexml.toUtf8());
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
