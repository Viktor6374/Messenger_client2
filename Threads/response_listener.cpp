#include "response_listener.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "../connections/responseparser.h"
#include <iostream>
#include "../connections/initializer.h"
#include "../connections/requestfactory.h"
#include "./response_listener_worker.h"
#include <QEventLoop>




Response_listener::Response_listener(const QHostAddress & host_address, quint16 port, QString login, QString password, Service * service) :
    _host_address(host_address),
    _port(port),
    _login(login),
    _password(password),
    _service(service)
{

}

QTcpSocket * Response_listener::get_socket()
{
    return _socket;
}

void Response_listener::run()
{
    try{
        Initializer init(_host_address, _port);
        _socket = init.initialize(_login, _password, _service);

        QEventLoop loop;
        Response_listener_worker worker(_socket, this);

        QObject::connect(this, SIGNAL(send_message_request(Message,QString)), &worker, SLOT(send_message(Message, QString)), Qt::QueuedConnection);
        QObject::connect(this, SIGNAL(add_new_chat_request(QString)), &worker, SLOT(add_new_chat(QString)), Qt::QueuedConnection);
        QObject::connect(this, SIGNAL(do_read()), &worker, SLOT(do_read_slot()), Qt::QueuedConnection);
        loop.exec();
    } catch (std::exception e){
        qDebug() << "Error: " << e.what();
        kill_application();
    }
}


void Response_listener::send_message(Message message, QString addressee)
{
    this->send_message_request(message, addressee);
}

void Response_listener::add_new_chat(QString username)
{
    qDebug() << "try add new chat";
    this->add_new_chat_request(username);
}

