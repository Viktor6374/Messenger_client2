#include "initializer.h"
#include <QJsonObject>
#include "./requestfactory.h"
#include "./responseparser.h"
#include <QByteArray>
#include <QVector>
#include "../Entities/interlocutor.h"
#include <string>
#include "../Threads/response_listener.h"
#include <iostream>
#include "../Threads/response_processing.h"


Initializer::Initializer(const QHostAddress & host_address, quint16 port)
{
    _socket = new QTcpSocket();
    _socket->connectToHost(host_address, port);

    if (!_socket->waitForConnected()) {
        throw std::logic_error("a connection error has occurred");
    }
}

QTcpSocket * Initializer::initialize(QString login, QString password, Service * service){
    QByteArray request = RequestFactory::initialization_request(login, password);
    _socket->write(request);
    _socket->waitForBytesWritten();

    qDebug() << "message recorded: " << request.toStdString();

    QByteArray response;

    //    Response_processing timeout;
    //    timeout.start();
    //    timeout.wait();
    if (_socket->waitForReadyRead(5000)) {
        response = _socket->readAll();
    }
    if (response.mid(response.length() - delimiter.length(), delimiter.length()) != delimiter){
        QString st = "Invalid server answer: " + QString::fromUtf8(response);
        throw std::logic_error(st.toStdString());
    }

    qDebug() << "message received: " << response.toStdString();

    response.chop(2);

    QVector<Interlocutor> users;

    CurrentUser user = ResponseParser::parse_initialization_response(response, users);

    service->init(users, user);

    return _socket;
}
