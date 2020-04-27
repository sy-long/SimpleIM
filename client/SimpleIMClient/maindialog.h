#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "socketconnect.h"
#include "chatdialog.h"
#include "addfriendsdialog.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QString Nowid,socketConnect *tsc, QWidget *parent = nullptr);
    ~MainDialog();

private slots:
    void on_pushButton_clicked();
    void slot_recvmessage();

private:
    Ui::MainDialog *ui;
    socketConnect *sc;
    QString id;
private:
    void closeEvent(QCloseEvent *e);
};

#endif // MAINDIALOG_H
