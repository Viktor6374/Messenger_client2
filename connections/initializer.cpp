#include "initializer.h"
#include <QJsonObject>
#include "./requestfactory.h"
#include "./responseparser.h"
#include <QByteArray>
#include <QVector>
#include "../Entities/interlocutor.h"
#include <string>
#include "../Threads/response_listener.h"

Initializer::Initializer(const QHostAddress & host_address, quint16 port)
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(host_address, port);

    if (!_socket->waitForConnected()) {
        throw std::exception("a connection error has occurred");
    }
}

std::pair<Service *, Response_listener *> Initializer::initialize(QString login, QString password){
    QByteArray request = RequestFactory::initialization_request(login, password);
    _socket->write(request);

    QByteArray response;
    while (1){
        response.append(_socket->readAll());
        if (response.mid(response.length() - delimiter.length(), delimiter.length()) == delimiter){
            break;
        }
    }

    QVector<Interlocutor> users;

    CurrentUser user = ResponseParser::parse_initialization_response(response, users);

    RequestConnection connection(_socket);

    Service * result = new Service(users, connection, user);

    Response_listener * listener = new Response_listener(_socket, result);

    return std::make_pair(result, listener);
}
