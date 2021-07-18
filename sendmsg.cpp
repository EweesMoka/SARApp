#include "sendmsg.h"
#include "ui_sendmsg.h"

#include <QTimer>

SendMsg::SendMsg(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SendMsg)
{
    ui->setupUi(this);
    ui->lineEdit->setText(tr("皮卡丘"));
    ui->textEdit->setText(tr("pikapikapi"));
    udpSocket = new QUdpSocket();
    setWindowTitle(tr("消息发出"));
    //setGeometry(100,100,200,200);
}

SendMsg::~SendMsg()
{
    delete ui;
}


void SendMsg::on_pushButton_clicked()
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendDatagram()));
    timer.start(1000);
    ui->pushButton->setEnabled(false);
}

void SendMsg::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << ui->lineEdit->text() << ui->textEdit->toPlainText();
    udpSocket->writeDatagram(datagram, QHostAddress::LocalHost, 5284);
}

void SendMsg::on_pushButton_2_clicked()
{
    timer.stop();
    ui->pushButton->setEnabled(true);
}
