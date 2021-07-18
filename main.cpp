#include "sendmsg.h"
#include "receivemsg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendMsg w;
    ReceiveMsg r;

    r.show();
    w.show();
    return a.exec();
}
