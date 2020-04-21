#ifndef REGISTEREDDIALOG_H
#define REGISTEREDDIALOG_H

#include <QDialog>

namespace Ui {
class registeredDialog;
}

class registeredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registeredDialog(QWidget *parent = nullptr);
    ~registeredDialog();

private:
    Ui::registeredDialog *ui;
};

#endif // REGISTEREDDIALOG_H
