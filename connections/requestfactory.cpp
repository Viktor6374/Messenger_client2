#include "requestfactory.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

QByteArray RequestFactory::initialization_request(QString login, QString password)
{
    QJsonObject request;
    request["command"] = "initialize";
    request["login"] = login;
    request["password"] = password;

    return JsonObject_to_byte_array(request);
}

QByteArray RequestFactory::JsonObject_to_byte_array(QJsonObject& obj)
{
    QJsonDocument doc = QJsonDocument(obj);
    return doc.toJson();
}
