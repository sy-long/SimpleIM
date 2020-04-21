#include "login.h"
#include "ui_logindialog.h"
#include<QDebug>

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
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
    registeredDialog registeredDialog(this);
    registeredDialog.exec();
}

