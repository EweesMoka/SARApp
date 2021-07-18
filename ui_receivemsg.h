/********************************************************************************
** Form generated from reading UI file 'receivemsg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEMSG_H
#define UI_RECEIVEMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReceiveMsg
{
public:
    QCheckBox *checkBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QTableView *tableView;

    void setupUi(QWidget *ReceiveMsg)
    {
        if (ReceiveMsg->objectName().isEmpty())
            ReceiveMsg->setObjectName(QString::fromUtf8("ReceiveMsg"));
        ReceiveMsg->resize(438, 338);
        checkBox = new QCheckBox(ReceiveMsg);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 10, 91, 31));
        radioButton = new QRadioButton(ReceiveMsg);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(370, 10, 115, 31));
        radioButton_2 = new QRadioButton(ReceiveMsg);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(310, 10, 61, 31));
        tableView = new QTableView(ReceiveMsg);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 40, 401, 281));

        retranslateUi(ReceiveMsg);

        QMetaObject::connectSlotsByName(ReceiveMsg);
    } // setupUi

    void retranslateUi(QWidget *ReceiveMsg)
    {
        ReceiveMsg->setWindowTitle(QApplication::translate("ReceiveMsg", "Form", nullptr));
        checkBox->setText(QApplication::translate("ReceiveMsg", "\346\216\245\346\224\266\346\266\210\346\201\257", nullptr));
        radioButton->setText(QApplication::translate("ReceiveMsg", "\351\273\221\345\244\234", nullptr));
        radioButton_2->setText(QApplication::translate("ReceiveMsg", "\347\231\275\345\244\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReceiveMsg: public Ui_ReceiveMsg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEMSG_H
