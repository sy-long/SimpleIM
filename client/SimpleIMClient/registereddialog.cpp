#include "registereddialog.h"
#include "ui_registereddialog.h"

registeredDialog::registeredDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registeredDialog)
{
    ui->setupUi(this);
}

registeredDialog::~registeredDialog()
{
    delete ui;
}
