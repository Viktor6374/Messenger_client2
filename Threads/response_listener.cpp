#include "response_listener.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "../connections/responseparser.h"


Response_listener::Response_listener(QTcpSocket * socket, Service * service, QObject *parent)
    : QThread{parent}
{
    _socket = socket;
    _service = service;
}

void Response_listener::run()
{
    QByteArray response;

    QByteArray byteArray = delimiter.toUtf8();

    QByteArrayView del(byteArray);
    while (1){
        if (_socket->waitForReadyRead()) {
            response.append(_socket->readAll());
            while (response.contains(del)) {
                int endIndex = response.indexOf(del) + delimiter.length();
                QByteArray message = response.left(endIndex);

                handle(message);

                response.remove(0, endIndex);
            }
        }
    }
}

void Response_listener::handle(QByteArray message)
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
    } else {
        throw std::exception("Incorrect format file");
    }
}

void Response_listener::handle_send_message(QJsonObject& message)
{
    std::pair<Message, QString> message_and_addressee = ResponseParser::parse_send_message_response(message);
    _service->set_answer_send_message(message_and_addressee.first, message_and_addressee.second);
    change_filling();
}

void Response_listener::handle_add_interlocutor(QJsonObject& message)
{
    Interlocutor interlocutor = ResponseParser::parse_add_new_chat_response(message);
    _service->set_answer_add_new_chat(interlocutor);
    change_filling();
}

void Response_listener::handle_new_message(QJsonObject& message)
{
    Message mess = ResponseParser::parse_new_message_response(message);
    _service->set_new_message(mess);
    change_filling();
}


