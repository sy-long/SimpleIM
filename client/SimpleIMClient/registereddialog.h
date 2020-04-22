#ifndef REGISTEREDDIALOG_H
#define REGISTEREDDIALOG_H

#include <QDialog>
#include "socketconnect.h"
#include <QMessageBox>

namespace Ui {
class registeredDialog;
}

class registeredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registeredDialog(socketConnect *tsc,QWidget *parent = nullptr);
    ~registeredDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::registeredDialog *ui;
    socketConnect *sc;
};

#endif // REGISTEREDDIALOG_H
