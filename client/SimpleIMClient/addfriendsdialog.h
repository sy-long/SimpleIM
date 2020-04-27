#ifndef ADDFRIENDSDIALOG_H
#define ADDFRIENDSDIALOG_H

#include <QDialog>
#include <socketconnect.h>

namespace Ui {
class AddfriendsDialog;
}

class AddfriendsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddfriendsDialog(QString Nowid,socketConnect *tsc, QWidget *parent = nullptr);
    ~AddfriendsDialog();

private slots:
    void on_pushButton_clicked();
    void slot_recvmessage();

private:
    Ui::AddfriendsDialog *ui;
    socketConnect *sc;
    QString id;
};

#endif // ADDFRIENDSDIALOG_H
