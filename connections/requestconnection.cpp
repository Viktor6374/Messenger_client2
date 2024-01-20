#include "requestconnection.h"
#include "./requestfactory.h"

RequestConnection::RequestConnection(QTcpSocket * socket) : _socket(socket)
{

}

void RequestConnection::addNewChat(QString username)
{
    QByteArray request = RequestFactory::add_new_user_request(username);
    _socket->write(request);
}

void RequestConnection::sendMessage(Message message, QString addressee)
{
    QByteArray request = RequestFactory::send_message_request(message, addressee);
    _socket->write(request);
}

RequestConnection::~RequestConnection()
{
    _socket->close();
    delete _socket;
}
