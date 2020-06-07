#ifndef UPDATADIALOG_H
#define UPDATADIALOG_H

#include <QDialog>
#include <socketconnect.h>

namespace Ui {
class updataDialog;
}

class updataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updataDialog(QString Nowid,socketConnect *tsc, QWidget *parent = nullptr);
    ~updataDialog();

private slots:
    void on_pushButton_clicked();
    void slot_recvmessage();

private:
    Ui::updataDialog *ui;
    socketConnect *sc;
    QString id;
};

#endif // UPDATADIALOG_H
