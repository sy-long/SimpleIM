#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "socketconnect.h"
#include "chatdialog.h"
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(socketConnect *tsc, QWidget *parent = nullptr);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    socketConnect *sc;
};

#endif // MAINDIALOG_H
