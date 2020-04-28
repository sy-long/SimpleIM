#ifndef CHATHELLODIALOG_H
#define CHATHELLODIALOG_H

#include <QDialog>

namespace Ui {
class ChatHelloDialog;
}

class ChatHelloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatHelloDialog(QWidget *parent = nullptr);
    ~ChatHelloDialog();

private:
    Ui::ChatHelloDialog *ui;
};

#endif // CHATHELLODIALOG_H
