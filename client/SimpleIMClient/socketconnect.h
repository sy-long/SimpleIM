#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H

#include <QTcpSocket>

class socketConnect
{
public:
    socketConnect();
public:
    bool isconnetion;
    QTcpSocket *TCP_sendMesSocket;
};

#endif // SOCKETCONNECT_H
