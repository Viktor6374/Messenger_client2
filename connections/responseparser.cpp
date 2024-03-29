#include "responseparser.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include "../Entities/history_messaging.h"

CurrentUser ResponseParser::parse_initialization_response(QByteArray response, QVector<Interlocutor>& result)
{
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QString st = "parsing error" + QString::fromUtf8(response);
    if (doc.isNull()){
        throw std::runtime_error(st.toStdString());
    }

    QJsonObject obj = doc.object();

    if (obj["command"] != "initialize"){
        throw std::logic_error("first message must be for initialization");
    }

    QJsonArray users = obj["users"].toArray();

    for (int i = 0; i < users.size(); i++){
        result.push_back(parse_interlocutor(users[i].toObject()));
    }
    QString username = obj.value("username").toString();
    QString first_name = obj.value("first_name").toString();
    QString second_name = obj.value("second_name").toString();

    CurrentUser user(username, first_name, second_name);

    return user;
}

std::pair<Message, QString> ResponseParser::parse_send_message_response(QJsonObject& message)
{
    QString sender = message.value("sender").toString();
    QString text = message.value("message").toString();
    QDateTime date_time = QDateTime::fromString(message.value("date_time").toString(), Qt::ISODate);

    QString addressee = message.value("addressee").toString();

    Message result(sender, text, date_time);
    return std::make_pair(result, addressee);
}

Message ResponseParser::parse_new_message_response(QJsonObject& message)
{
    QString sender = message.value("sender").toString();
    QString text = message.value("message").toString();
    QDateTime date_time = QDateTime::fromString(message.value("date_time").toString(), Qt::ISODate);

    Message result(sender, text, date_time);
    return result;
}

Interlocutor ResponseParser::parse_add_new_chat_response(QJsonObject& message)
{
    try{
        QString username = message.value("username").toString();
        QString first_name = message.value("first_name").toString();
        QString second_name = message.value("second_name").toString();
        Interlocutor interlocutor(username, first_name, second_name);
        return interlocutor;
    } catch (std::exception e){
        qDebug() << e.what();
    }
}



Interlocutor ResponseParser::parse_interlocutor(QJsonObject interlocutor)
{
    QString username = interlocutor.value("username").toString();
    QString first_name = interlocutor.value("first_name").toString();
    QString second_name = interlocutor.value("second_name").toString();
    Interlocutor result(username, first_name, second_name);

    QJsonArray messages = interlocutor["messages"].toArray();

    for (int i = 0; i < messages.size(); i++){
        Message cur_message = parse_message(messages[i].toObject());
        result.get_history_messaging().add_message(cur_message);
    }
    qDebug() << "mess" << result.get_history_messaging().get_quantity_messages();
//    qDebug() << "mess2" << history.get_quantity_messages();
    return result;
}

Message ResponseParser::parse_message(QJsonObject message)
{
    QString sender_username = message.value("sender_username").toString();
    QString message_str = message.value("message").toString();
    QString send_time_str =message.value("send_time").toString();
    QDateTime send_time = QDateTime::fromString(send_time_str, Qt::ISODate);

    Message result(sender_username, message_str, send_time);

    return result;
}

