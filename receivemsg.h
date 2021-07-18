#ifndef RECEIVEMSG_H
#define RECEIVEMSG_H

#include "slidebutton.h"

#include <QWidget>
#include <QUdpSocket>
#include <QStandardItemModel>
#include <QTableView>
#include <QTimer>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>


class ReceiveMsg : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveMsg(QWidget *parent = nullptr);
    ~ReceiveMsg();

private slots:
    void processPendingDatagrams();
    void timelyClear();
    void isReceiveOrNot();
    void toWhiteStyle();

    void toBlackStyle();


private:

    QStandardItemModel *model;
    QTableView *tableView;
    QTimer timer;
    QUdpSocket *udpSocket;

    QRadioButton *whiteStyle;
    QRadioButton *blackStyle;
    SlideButton *slideButton;
    QLabel *receiveOrNot;
    QLabel *Style;
    QGroupBox *settings;

};

#endif // RECEIVEMSG_H
