#include "receivemsg.h"
#include "ui_receivemsg.h"

#include <QDateTime>
#include <QUdpSocket>
#include <QDebug>
#include <QStyleFactory>
#include <QScrollBar>
#include<iostream>
#include <QFile>
#include <QGridLayout>
using namespace std;
ReceiveMsg::ReceiveMsg(QWidget *parent) :
    QWidget(parent)
{
    model=new QStandardItemModel(0, 3, parent);
    model->setHorizontalHeaderLabels(QStringList()<<"发送人"<<"内容"<<"时间");

    tableView = new QTableView;
    tableView->setAlternatingRowColors(true);
    tableView->setModel(model);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(2,Qt::AscendingOrder);

    udpSocket = new QUdpSocket();
    udpSocket->bind(5284);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));


    settings = new QGroupBox(tr("设置"));
    receiveOrNot =new QLabel(tr("接收消息"));
    Style =new QLabel(tr("皮肤风格"));
    slideButton =new SlideButton;
    slideButton->setToggle(true);
    whiteStyle=new QRadioButton(tr("白色扁平"));
    blackStyle=new QRadioButton(tr("黑色扁平"));
    connect(slideButton,SIGNAL(toggled(bool)),this,SLOT(isReceiveOrNot()));
    connect(whiteStyle,SIGNAL(clicked()),this,SLOT(toWhiteStyle()));
    connect(blackStyle,SIGNAL(clicked()),this,SLOT(toBlackStyle()));
    this->whiteStyle->setChecked(true);//放在udp
    toWhiteStyle();

    QGridLayout *settingLayout=new QGridLayout;
    settingLayout->addWidget(receiveOrNot,0,0);
    settingLayout->addWidget(slideButton,0,1,Qt::AlignRight);
    settingLayout->addWidget(Style,1,0,1,2);
    settingLayout->addWidget(whiteStyle,1,1,Qt::AlignRight);
    settingLayout->addWidget(blackStyle,2,1,Qt::AlignRight);
    settings->setLayout(settingLayout);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(settings);

    setLayout(mainLayout);
    setGeometry(300,300,500,500);
    setWindowTitle(tr("消息接收"));
}

ReceiveMsg::~ReceiveMsg()
{
}

void ReceiveMsg::processPendingDatagrams()
{

    QByteArray datagram;

    do{
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    }while(udpSocket->hasPendingDatagrams());

    QString Name;
    QString Context;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_9);
    in >> Name >> Context;

    QDateTime date = QDateTime::currentDateTime();

    model->insertRow(0);
    model->setData(model->index(0,0), Name);
    model->setData(model->index(0,1),Context);
    model->setData(model->index(0,2),date);




    timer.stop();
    connect(&timer,SIGNAL(timeout()),this,SLOT(timelyClear()));
    timer.start(10*1000);
    return;
}


void ReceiveMsg::timelyClear()
{
    int rowCount=model->rowCount();
    for(int r=rowCount;r>=0;--r)
    {
        model->removeRow(r);
    }
}





void ReceiveMsg::isReceiveOrNot()
{
    if(!this->slideButton->isToggled())
    {
        this->udpSocket->blockSignals(true);
        return;
    }else{
        this->udpSocket->blockSignals(false);
        emit this->udpSocket->readyRead();//这里应该加一个判定，当有数据发过来的时候才发送信号。
        return;
    }
}

void ReceiveMsg::toWhiteStyle()//白天风格
{
    this->setStyleSheet(
                        "QHeaderView{"
                        "color: black;"
                        "border: rgb(245,245,245);"
                        "border-bottom: 3px solid rgb(0, 160, 230);"
                        "background: rgb(245,245,245);"
                        "min-height: 30px;"
                        "}"
                        "QHeaderView::section:horizontal {"
                        "border: none;"
                        "color: black;"
                        "background: rgb(245,245,245);"
                        "padding-left: 5px;"
                        "}"
                        "QHeaderView::section:vertical {"
                        "border: none;"
                        "color: black;"
                        "background: rgb(245,245,245);"
                        "padding-left: 5px;"
                        "}"
                        "QHeaderView::section:horizontal:hover {"
                        "background: rgb(0, 160, 230);"
                        "}"
                        "QHeaderView::section:horizontal:pressed {"
                        "background: rgb(0, 180, 255);"
                        "}"
                        "QHeaderView::up-arrow {"
                        "width: 13px;"
                        "height: 11px;"
                        "padding-right: 5px;"
                        "subcontrol-position: center right;"
                        "}"
                        "QHeaderView::down-arrow {"
                        "width: 13px;"
                        "height: 11px;"
                        "padding-right: 5px;"
                        "subcontrol-position: center right;"
                        "}"

                        "QTableView {"
                        "border:1px solid rgb(240,240,240);"
                        "background: rgb(250,250,250);"
                        "color:black;"
                        "border-bottom: rgb(0, 160, 230);"
                        "alternate-background-color:rgb(245, 245, 245);"
                        "}"
                        "QTableView QTableCornerButton::section"
                        "{"
                        "background:rgb(240,240,240);"
                        "}"
                        "QTableView QTableCornerButton::section:pressed"
                        "{"
                        "background:rgb(0,160,230);"
                        "}"
                        "QGroupBox{"
                        "color:black;"
                        "}"
                        "QLabel{"
                        "color:black;"
                        "}"



                );
    whiteStyle->setStyleSheet("QRadioButton {"
                                     "color: black;"
                                     "}");
    blackStyle->setStyleSheet("QRadioButton {"
                                     "color: black;"
                                     "}");
    receiveOrNot->setStyleSheet("QCheckBox {"
                                     "color: black;"
                                     "}");
    tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                      "padding-top:20px;"
                                                      "padding-bottom:20px;"
                                                      "padding-left:2px;"
                                                      "padding-right:2px;"
                                                      "background: rgb(245,245,245);"
                                                      "}"
                                                      "QScrollBar::handle:vertical {"
                                                      "height: 20px;"
                                                      "border:1px solid rgb(190,190,190);"
                                                      "border-radius:2px;"
                                                      "background-color: rgb(220,220,220);"
                                                      "}"
                                                      "QScrollBar::handle:vertical:hover {"
                                                      " background-color: rgb(190,190,190);"
                                                      "}"
                                                      "QScrollBar::sub-line:vertical {"
                                                      "height: 20px;"
                                                      "background: rgb(245,245,245);"
                                                      "image:url(:/black/up.png);"
                                                      "subcontrol-position: top;"
                                                      "}"
                                                      "QScrollBar::add-line:vertical {"
                                                      "height: 20px;"
                                                      "background: rgb(245,245,245);"
                                                      "subcontrol-position: bottom;"
                                                      "image:url(:/black/down.png);"
                                                      "}"
                                                      "QScrollBar::sub-line:vertical:hover {"
                                                      "background: rgb(245,245,245);"
                                                      "}"
                                                      "QScrollBar::add-line:vertical:hover {"
                                                      "background: rgb(245,245,245);"
                                                      "}"
                                                      "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                                      "background:rgb(245,245,245);"
                                                      "}"
                                                      );
    tableView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
                                                        "padding-left:20px;"
                                                        "padding-right:20px;"
                                                        "padding-top:2px;"
                                                        "padding-bottom:2px;"
                                                        "background: rgb(245,245,245);"
                                                        "}"
                                                        "QScrollBar::handle:horizontal {"
                                                        "height: 20px;"
                                                        "border:1px solid rgb(190,190,190);"
                                                        "border-radius:2px;"
                                                        "background-color: rgb(220,220,220);"
                                                        "}"
                                                        "QScrollBar::handle:horizontal:hover {"
                                                        "background-color: rgb(190,190,190);"
                                                        "}"
                                                        "QScrollBar::sub-line:horizontal {"
                                                        "width: 20px;"
                                                        "background: rgb(245,245,245);"
                                                        "image:url(:/black/left.png);"
                                                        "subcontrol-position: left;"
                                                        "}"
                                                        "QScrollBar::add-line:horizontal {"
                                                        "width: 20px;"
                                                        "background: rgb(245,245,245);"
                                                        "image:url(:/black/right.png);"
                                                        "subcontrol-position: right;"
                                                        "}"
                                                        "QScrollBar::sub-line:horizontal:hover {"
                                                        "background: rgb(245,245,245);"
                                                        "}"
                                                        "QScrollBar::add-line:horizontal:hover {"
                                                        "background: rgb(245,245,245);"
                                                        "}"
                                                        "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal {"
                                                        "background: rgb(245,245,245);"
                                                        "}"
                                                        );
    QPalette palette;
    palette.setColor(QPalette::Window,QColor(230,230,230));
    palette.setColor(QPalette::WindowText,Qt::black);
    palette.setColor(QPalette::Text,Qt::black);
    this->setPalette(palette);
}
void ReceiveMsg::toBlackStyle()
{
    this->setStyleSheet(
                        "QHeaderView{"
                        "color: white;"
                        "border: rgb(150,150,150);"
                        "border-bottom: 3px solid rgb(0, 160, 230);"
                        "background: rgb(57, 58, 60);"
                        "min-height: 30px;"
                        "}"
                        "QHeaderView::section:horizontal {"
                        "border: none;"
                        "color: white;"
                        "background: rgb(80,80,80);"
                        "padding-left: 5px;"
                        "}"
                        "QHeaderView::section:vertical {"
                        "border: none;"
                        "color: white;"
                        "background: rgb(80,80,80);"
                        "padding-left: 5px;"
                        "}"
                        "QHeaderView::section:horizontal:hover {"
                        "background: rgb(0, 160, 230);"
                        "}"
                        "QHeaderView::section:horizontal:pressed {"
                        "background: rgb(0, 180, 255);"
                        "}"
                        "QHeaderView::up-arrow {"
                        "width: 13px;"
                        "height: 11px;"
                        "padding-right: 5px;"
                        "subcontrol-position: center right;"
                        "}"
                        "QHeaderView::down-arrow {"
                        "width: 13px;"
                        "height: 11px;"
                        "padding-right: 5px;"
                        "subcontrol-position: center right;"
                        "}"

                        "QTableView {"
                        "border:none;"
                        "background: rgb(120,120,120);"
                        "color:white;"
                        "border-bottom: rgb(0, 160, 230);"
                        "alternate-background-color:rgb(80, 80, 80);"
                        "}"
                        "QTableView QTableCornerButton::section"
                        "{"
                        "background:rgb(50,50,50);"
                        "}"
                        "QTableView QTableCornerButton::section:pressed"
                        "{"
                        "background:rgb(0,160,230);"
                        "}"
                        "QGroupBox{"
                        "color:white;"
                        "border: 1px solid gray;"
                        "}"
                        "QLabel{"
                        "color:white;"
                        "}"



                );
    whiteStyle->setStyleSheet("QRadioButton {"
                                     "color: white;"
                                     "}");
    blackStyle->setStyleSheet("QRadioButton {"
                                     "color: white;"
                                     "}");
    receiveOrNot->setStyleSheet("QCheckBox {"
                                     "color: white;"
                                     "}");
    tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                      "padding-top:20px;"
                                                      "padding-bottom:20px;"
                                                      "padding-left:2px;"
                                                      "padding-right:2px;"
                                                      "background: rgb(68,69,73);"
                                                      "}"
                                                      "QScrollBar::handle:vertical {"
                                                      "height: 20px;"
                                                      "border:1px solid rgb(68,69,73);"
                                                      "border-radius:2px;"
                                                      "background-color: rgb(130,130,130);"
                                                      "}"
                                                      "QScrollBar::handle:vertical:hover {"
                                                      " background-color: rgb(170,170,170);"
                                                      "}"
                                                      "QScrollBar::sub-line:vertical {"
                                                      "height: 20px;"
                                                      "background: rgb(80,80,80);"
                                                      "image:url(:/black/up.png);"
                                                      "subcontrol-position: top;"
                                                      "}"
                                                      "QScrollBar::add-line:vertical {"
                                                      "height: 20px;"
                                                      "background: rgb(80,80,80);"
                                                      "subcontrol-position: bottom;"
                                                      "image:url(:/black/down.png);"
                                                      "}"
                                                      "QScrollBar::sub-line:vertical:hover {"
                                                      "background: rgb(68, 69, 73);"
                                                      "}"
                                                      "QScrollBar::add-line:vertical:hover {"
                                                      "background: rgb(68, 69, 73);"
                                                      "}"
                                                      "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                                      "background:rgb(68, 69, 73);"
                                                      "}"
                                                      );
    tableView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {"
                                                        "padding-left:20px;"
                                                        "padding-right:20px;"
                                                        "padding-top:2px;"
                                                        "padding-bottom:2px;"
                                                        "background: rgb(68,69,73);"
                                                        "}"
                                                        "QScrollBar::handle:horizontal {"
                                                        "height: 20px;"
                                                        "border:1px solid rgb(68,69,73);"
                                                        "border-radius:2px;"
                                                        "background-color: rgb(130,130,130);"
                                                        "}"
                                                        "QScrollBar::handle:horizontal:hover {"
                                                        "background-color: rgb(170,170,170);"
                                                        "}"
                                                        "QScrollBar::sub-line:horizontal {"
                                                        "width: 20px;"
                                                        "background: rgb(80,80,80);"
                                                        "image:url(:/black/left.png);"
                                                        "subcontrol-position: left;"
                                                        "}"
                                                        "QScrollBar::add-line:horizontal {"
                                                        "width: 20px;"
                                                        "background: rgb(80,80,80);"
                                                        "image:url(:/black/right.png);"
                                                        "subcontrol-position: right;"
                                                        "}"
                                                        "QScrollBar::sub-line:horizontal:hover {"
                                                        "background: rgb(68, 69, 73);"
                                                        "}"
                                                        "QScrollBar::add-line:horizontal:hover {"
                                                        "background: rgb(68, 69, 73);"
                                                        "}"
                                                        "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal {"
                                                        "background: rgb(130,130,130);"
                                                        "}"
                                                        );
    QPalette palette;
    palette.setColor(QPalette::Window,QColor(60,60,60));
    palette.setColor(QPalette::WindowText,Qt::white);
    palette.setColor(QPalette::Text,Qt::white);
    this->setPalette(palette);
}

