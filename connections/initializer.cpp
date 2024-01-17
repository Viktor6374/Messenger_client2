#include "initializer.h"
#include <QJsonObject>
#include "./requestfactory.h"
#include "./responseparser.h"
#include <QByteArray>
#include <QVector>
#include "../Entities/interlocutor.h"
#include <string>

Initializer::Initializer(const QHostAddress & host_address, quint16 port) : delimiter("/n")
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(host_address, port);

    if (!_socket->waitForConnected()) {
        throw std::exception("a connection error has occurred");
    }
}

Service * Initializer::initialize(QString login, QString password){
    QByteArray request = RequestFactory::initialization_request(login, password);
    _socket->write(request);

    QByteArray response;
    while (1){
        response.append(_socket->readAll());
        if (response.mid(response.length() - delimiter.length(), delimiter.length()) == delimiter){
            break;
        }
    }

    QVector<Interlocutor> users = ResponseParser::parse_initialization_response(response);
    QMap<QString, Interlocutor> users_map;

    for (int i = 0; i < users.size(); i++){
        users_map[users[i].get_username()] = users[i];
    }

    RequestConnection connection(_socket);

    Service * result = new Service(users_map, connection);

    return result;
}
