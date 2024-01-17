#include "requestconnection.h"

RequestConnection::RequestConnection(QTcpSocket * socket) : _socket(socket)
{

}

bool RequestConnection::addNewChat(QString username)
{
    return false;
}

bool RequestConnection::sendMessage(Message message, QString addressee)
{
    return false;
}

RequestConnection::~RequestConnection()
{
    _socket->close();
    delete _socket;
}
