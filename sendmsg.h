#ifndef SENDMSG_H
#define SENDMSG_H

#include <QWidget>
#include <QUdpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class SendMsg; }
QT_END_NAMESPACE

class SendMsg : public QWidget
{
    Q_OBJECT

public:
    SendMsg(QWidget *parent = nullptr);
    ~SendMsg();

private slots:
    void on_pushButton_clicked();
    void sendDatagram();
    void on_pushButton_2_clicked();

private:
    Ui::SendMsg *ui;
    QTimer timer;
    QUdpSocket *udpSocket;
};
#endif // SENDMSG_H
