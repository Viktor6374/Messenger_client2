#ifndef REQUESTCONNECTION_H
#define REQUESTCONNECTION_H

#include "../Entities/message.h"
#include <QString>
#include <QTcpSocket>


class RequestConnection
{
public:
    RequestConnection(QTcpSocket * socket);
    void addNewChat(QString username);
    void sendMessage(Message message, QString addressee);
    ~RequestConnection();
private:
    QTcpSocket *_socket;
};

#endif // REQUESTCONNECTION_H
