#include "chathellodialog.h"
#include "ui_chathellodialog.h"

ChatHelloDialog::ChatHelloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatHelloDialog)
{
    ui->setupUi(this);
}

ChatHelloDialog::~ChatHelloDialog()
{
    delete ui;
}
