/********************************************************************************
** Form generated from reading UI file 'sendmsg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDMSG_H
#define UI_SENDMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendMsg
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *SendMsg)
    {
        if (SendMsg->objectName().isEmpty())
            SendMsg->setObjectName(QString::fromUtf8("SendMsg"));
        SendMsg->resize(286, 118);
        label = new QLabel(SendMsg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 11, 60, 16));
        lineEdit = new QLineEdit(SendMsg);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(93, 11, 181, 21));
        label_2 = new QLabel(SendMsg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(11, 39, 75, 16));
        textEdit = new QTextEdit(SendMsg);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(93, 39, 181, 31));
        pushButton = new QPushButton(SendMsg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 80, 81, 28));
        pushButton_2 = new QPushButton(SendMsg);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 80, 81, 28));

        retranslateUi(SendMsg);

        QMetaObject::connectSlotsByName(SendMsg);
    } // setupUi

    void retranslateUi(QWidget *SendMsg)
    {
        SendMsg->setWindowTitle(QApplication::translate("SendMsg", "SendMsg", nullptr));
        label->setText(QApplication::translate("SendMsg", "\345\217\221\344\273\266\344\272\272\357\274\232", nullptr));
        label_2->setText(QApplication::translate("SendMsg", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        pushButton->setText(QApplication::translate("SendMsg", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        pushButton_2->setText(QApplication::translate("SendMsg", "\345\201\234\346\255\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendMsg: public Ui_SendMsg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDMSG_H
