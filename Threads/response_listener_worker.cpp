#include "response_listener_worker.h"
#include "../connections/requestfactory.h"
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include "../connections/responseparser.h"
#include <iostream>
#include "../connections/initializer.h"
#include "../connections/requestfactory.h"


Response_listener_worker::Response_listener_worker(QTcpSocket * socket, Response_listener * listener)
{
    _socket = socket;
    _lisener = listener;
}

void Response_listener_worker::send_message(Message message, QString addressee)
{
    QByteArray request = RequestFactory::send_message_request(message, addressee);
    _socket->write(request);
    _socket->waitForBytesWritten();

    qDebug() << "message recorded: " << request.toStdString();
}

void Response_listener_worker::add_new_chat(QString username)
{
    qDebug() << "message recorded";
    QByteArray request = RequestFactory::add_new_user_request(username);
    _socket->write(request);
    _socket->waitForBytesWritten();

    qDebug() << "message recorded: " << request.toStdString();
}


void Response_listener_worker::do_read_slot()
{
    QByteArray byteArray = QByteArray::fromStdString("/n");
    QByteArrayView delimiter = QByteArrayView(byteArray);

    qDebug() << "try read";
    try{
        if (_socket->waitForReadyRead(1000)) {
            qDebug() << "read begin";
            response.append(_socket->readAll());
            while (response.contains(delimiter)) {
                int endIndex = response.indexOf(delimiter) + (delimiter).length();
                QByteArray message = response.left(endIndex);
                qDebug() << "message received: " << message.toStdString();

                message.chop(2);
                handle(message);

                response.remove(0, endIndex);
            }
        }
    } catch(std::exception e){
        qDebug() << e.what();
    }

    emit _lisener->do_read();
}

void Response_listener_worker::handle(QByteArray message)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(message);

    QJsonObject jsonMessage;

    if (!jsonDocument.isNull() && jsonDocument.isObject()) {
        jsonMessage = jsonDocument.object();
    } else {
        throw std::exception("Incorrect format file");
    }

    QString command = jsonMessage.value("command").toString();
    if (command == "send_message"){
        handle_send_message(jsonMessage);
    } else if (command == "add_interlocutor"){
        handle_add_interlocutor(jsonMessage);
    } else if (command == "new_message"){
        handle_new_message(jsonMessage);
    } else if (command == "error"){
        handle_error(jsonMessage);
    }else {
        throw std::exception("Incorrect format file");
    }
}

void Response_listener_worker::handle_send_message(QJsonObject& message)
{
    std::pair<Message, QString> message_and_addressee = ResponseParser::parse_send_message_response(message);
    _lisener->send_message_response(message_and_addressee.first, message_and_addressee.second);

}

void Response_listener_worker::handle_add_interlocutor(QJsonObject& message)
{
    Interlocutor interlocutor = ResponseParser::parse_add_new_chat_response(message);
    qDebug() << "1";
    _lisener->add_new_chat_response(interlocutor);

}

void Response_listener_worker::handle_new_message(QJsonObject& message)
{
    Message mess = ResponseParser::parse_new_message_response(message);
    _lisener->new_message(mess);

}

void Response_listener_worker::handle_error(QJsonObject& message)
{
    QString text = message.value("text").toString();
    qDebug() << "Server error: " << text;
}
