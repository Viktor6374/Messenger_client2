#ifndef RESPONSE_LISTENER_WORKER_H
#define RESPONSE_LISTENER_WORKER_H

#include <QObject>
#include <QTcpSocket>
#include "../Entities/message.h"
#include "../Threads/response_listener.h"

class Response_listener;

class Response_listener_worker : public QObject
{
    Q_OBJECT
public:
    Response_listener_worker(QTcpSocket * socket, Response_listener * listener);
public slots:
    void send_message(Message message, QString addressee);
    void add_new_chat(QString username);
    void do_read_slot();
private:
    QTcpSocket * _socket;
    QByteArray response;
    Response_listener * _lisener;
    void handle(QByteArray message);
    void handle_send_message(QJsonObject& message);
    void handle_add_interlocutor(QJsonObject& message);
    void handle_new_message(QJsonObject& message);
    void handle_error(QJsonObject& message);
};

#endif // RESPONSE_LISTENER_WORKER_H
