#include "service.h"

Service::Service(QMap<QString, Interlocutor>& users, RequestConnection& connection) : _users(users), _connection(connection)
{

}
