#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDebug>
MainDialog::MainDialog(socketConnect *tsc,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    sc(tsc)
{
    ui->setupUi(this);

}

MainDialog::~MainDialog()
{
    delete ui;
}
