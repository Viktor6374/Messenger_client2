#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include <QString>
#include <QJsonObject>
#include "../Entities/message.h"

class RequestFactory
{
public:
    static QByteArray initialization_request(QString login, QString password);
    static QByteArray send_message_request(Message message, QString addressee);
    static QByteArray add_new_user_request(QString username);
private:
    static QByteArray JsonObject_to_byte_array(QJsonObject& obj);
};

#endif // REQUESTFACTORY_H
