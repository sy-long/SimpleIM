/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(500, 300);
        label = new QLabel(loginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 481, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(loginDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(120, 180, 131, 21));
        label_2 = new QLabel(loginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 180, 24, 16));
        label_3 = new QLabel(loginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 220, 24, 16));
        lineEdit_2 = new QLineEdit(loginDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 220, 131, 21));
        pushButton = new QPushButton(loginDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 180, 80, 20));
        pushButton_2 = new QPushButton(loginDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 220, 80, 20));

        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QApplication::translate("loginDialog", "loginDialog", nullptr));
        label->setText(QApplication::translate("loginDialog", "SimpleIM", nullptr));
        label_2->setText(QApplication::translate("loginDialog", "\350\264\246\345\217\267", nullptr));
        label_3->setText(QApplication::translate("loginDialog", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QApplication::translate("loginDialog", "\346\263\250\345\206\214", nullptr));
        pushButton_2->setText(QApplication::translate("loginDialog", "\347\231\273\351\231\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
