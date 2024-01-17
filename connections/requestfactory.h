#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include <QString>
#include <QJsonObject>

class RequestFactory
{
public:
    static QByteArray initialization_request(QString login, QString password);
private:
    static QByteArray JsonObject_to_byte_array(QJsonObject& obj);
};

#endif // REQUESTFACTORY_H
