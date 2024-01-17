#ifndef REQUESTCONNECTION_H
#define REQUESTCONNECTION_H

#include "../Entities/message.h"
#include <QString>
#include <QTcpSocket>


class RequestConnection
{
public:
    RequestConnection(QTcpSocket * socket);
    bool addNewChat(QString username);
    bool sendMessage(Message message, QString addressee);
    ~RequestConnection();
private:
    QTcpSocket *_socket;
};

#endif // REQUESTCONNECTION_H
