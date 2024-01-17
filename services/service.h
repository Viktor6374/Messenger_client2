#ifndef SERVICE_H
#define SERVICE_H
#include <QMap>
#include <QString>
#include "../Entities/interlocutor.h"
#include "../connections/requestconnection.h"

class Service
{
public:
    Service(QMap<QString, Interlocutor>& users, RequestConnection& connection);
private:
    QMap<QString, Interlocutor> _users;
    RequestConnection _connection;
};

#endif // SERVICE_H
