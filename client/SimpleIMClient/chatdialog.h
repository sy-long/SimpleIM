#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QDebug>
#include "socketconnect.h"

namespace Ui {
class chatDialog;
}

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatDialog(QString Nowid,socketConnect *tsc,QWidget *parent = nullptr);
    ~chatDialog();

private:
    Ui::chatDialog *ui;
    socketConnect *sc;
    QString id;

public:
    void sent_message(QString uid);
    void get_message(QString uid,QString text);
};

#endif // CHATDIALOG_H
