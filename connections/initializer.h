#ifndef INITIALIZER_H
#define INITIALIZER_H
#include <QTcpSocket>
#include "../services/service.h"
#include "../Threads/response_listener.h"

class Initializer : QObject
{
public:
    Initializer(const QHostAddress & host_address, quint16 port);
    std::pair<Service *, Response_listener *> initialize(QString login, QString password);
private:
    QTcpSocket *_socket;
    const QString delimiter = "/n";
};

#endif // INITIALIZER_H
