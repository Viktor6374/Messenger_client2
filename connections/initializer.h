#ifndef INITIALIZER_H
#define INITIALIZER_H
#include <QTcpSocket>
#include "../services/service.h"

class Initializer : QObject
{
public:
    Initializer(const QHostAddress & host_address, quint16 port);
    Service * initialize(QString login, QString password);
private:
    QTcpSocket *_socket;
    const QString delimiter;
};

#endif // INITIALIZER_H
