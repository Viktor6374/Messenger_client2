#include "responseparser.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include "../Entities/history_messaging.h"

QVector<Interlocutor> ResponseParser::parse_initialization_response(QByteArray response)
{
    QJsonDocument doc = QJsonDocument::fromJson(response);

    if (doc.isNull()){
        throw std::runtime_error("parsing error");
    }

    QJsonObject obj = doc.object();

    if (obj["command"] != "initialize"){
        throw std::logic_error("first message must be for initialization");
    }

    QJsonArray users = obj["users"].toArray();
    QVector<Interlocutor> result;

    for (int i = 0; i < users.size(); i++){
        result.push_back(parse_interlocutor(users[i].toObject()));
    }

    return result;
}

Interlocutor ResponseParser::parse_interlocutor(QJsonObject interlocutor)
{
    QString username = interlocutor.value("username").toString();
    QString first_name = interlocutor.value("first_name").toString();
    QString second_name = interlocutor.value("second_name").toString();
    Interlocutor result(username, first_name, second_name);

    QJsonArray messages = interlocutor["messages"].toArray();
    History_messaging history = result.get_history_messaging();

    for (int i = 0; i < messages.size(); i++){
        history.add_message(parse_message(messages[i].toObject()));
    }

    return result;
}

Message& ResponseParser::parse_message(QJsonObject message)
{
    QString sender_username = message.value("sender_username").toString();
    QString message_str = message.value("message").toString();
    QString send_time_str =message["send_time"].toString();
    QDateTime send_time = QDateTime::fromString(send_time_str, Qt::ISODate);

    Message result(sender_username, message_str, send_time);

    return result;
}

