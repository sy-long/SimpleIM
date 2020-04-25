#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDialog)
{
    ui->setupUi(this);
}

chatDialog::~chatDialog()
{
    delete ui;
}
