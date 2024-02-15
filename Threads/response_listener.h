#ifndef RESPONSE_LISTENER_H
#define RESPONSE_LISTENER_H

#include <QThread>
#include <QTcpSocket>

#include "../services/service.h"
#include <QJsonObject>

class Response_listener : public QThread
{
    Q_OBJECT
public:
    explicit Response_listener(const QHostAddress & host_address, quint16 port, QString login, QString password, Service * service);
    void run() override;
    QTcpSocket * get_socket();
private:

    QHostAddress _host_address;
    quint16 _port;
    QString _login;
    QString _password;
    Service * _service;


    QTcpSocket * _socket;
signals:
    void send_message_response(Message message, QString addressee);
    void add_new_chat_response(Interlocutor new_interlocutor);
    void send_message_request(Message message, QString addressee);
    void add_new_chat_request(QString username);
    void new_message(Message message);
    void do_read();
    void kill_application();
public slots:
    void send_message(Message message, QString addressee);
    void add_new_chat(QString username);
};

#endif // RESPONSE_LISTENER_H
