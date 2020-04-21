#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "registereddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginDialog; }
QT_END_NAMESPACE

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::loginDialog *ui;
};
#endif // LOGINDIALOG_H
