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

QByteArray RequestFactory::send_message_request(Message message, QString addressee)
{
    QJsonObject request;
    request["command"] = "send_message";
    request["time"] = message.get_send_time().toString(Qt::ISODate);
    request["sender"] = message.get_sender_username();
    request["addressee"] = addressee;
    request["message"] = message.get_message();

    return JsonObject_to_byte_array(request);
}

QByteArray RequestFactory::add_new_user_request(QString username)
{
    QJsonObject request;
    request["command"] = "add_new_user";
    request["username"] = username;

    return JsonObject_to_byte_array(request);
}

QByteArray RequestFactory::JsonObject_to_byte_array(QJsonObject& obj)
{
    QJsonDocument doc = QJsonDocument(obj);

    QString del_str("/n");
    QByteArray del = del_str.toUtf8();
    QByteArray result = doc.toJson();
    result.append(del);
    return result;
}
