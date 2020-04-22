/********************************************************************************
** Form generated from reading UI file 'registereddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTEREDDIALOG_H
#define UI_REGISTEREDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registeredDialog
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QLabel *label_5;

    void setupUi(QDialog *registeredDialog)
    {
        if (registeredDialog->objectName().isEmpty())
            registeredDialog->setObjectName(QString::fromUtf8("registeredDialog"));
        registeredDialog->resize(462, 442);
        label_2 = new QLabel(registeredDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 130, 31, 20));
        label_3 = new QLabel(registeredDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 210, 71, 20));
        label_4 = new QLabel(registeredDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(140, 290, 31, 20));
        lineEdit = new QLineEdit(registeredDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 50, 113, 20));
        lineEdit_2 = new QLineEdit(registeredDialog);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 130, 113, 20));
        lineEdit_3 = new QLineEdit(registeredDialog);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(180, 210, 113, 20));
        lineEdit_4 = new QLineEdit(registeredDialog);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(182, 290, 111, 21));
        pushButton = new QPushButton(registeredDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 380, 80, 20));
        label_5 = new QLabel(registeredDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(140, 50, 31, 20));

        retranslateUi(registeredDialog);

        QMetaObject::connectSlotsByName(registeredDialog);
    } // setupUi

    void retranslateUi(QDialog *registeredDialog)
    {
        registeredDialog->setWindowTitle(QApplication::translate("registeredDialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("registeredDialog", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QApplication::translate("registeredDialog", "\345\206\215\346\254\241\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_4->setText(QApplication::translate("registeredDialog", "\345\220\215\347\247\260", nullptr));
        pushButton->setText(QApplication::translate("registeredDialog", "\347\241\256\345\256\232", nullptr));
        label_5->setText(QApplication::translate("registeredDialog", "\350\264\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registeredDialog: public Ui_registeredDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTEREDDIALOG_H
