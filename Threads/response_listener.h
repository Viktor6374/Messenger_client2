#ifndef RESPONSE_LISTENER_H
#define RESPONSE_LISTENER_H

#include <QThread>
#include <QTcpSocket>
#include "../windows/mainwindow.h"
#include "../services/service.h"
#include <QJsonObject>

class Response_listener : public QThread
{
    Q_OBJECT
public:
    explicit Response_listener(QTcpSocket * socket, Service * service, QObject *parent = nullptr);
    void run() override;
private:
    QTcpSocket * _socket;
    Service * _service;
    const QString delimiter = "/n";
    void handle(QByteArray message);
    void handle_send_message(QJsonObject& message);
    void handle_add_interlocutor(QJsonObject& message);
    void handle_new_message(QJsonObject& message);
signals:
    void change_filling();
};

#endif // RESPONSE_LISTENER_H
