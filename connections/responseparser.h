#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H
#include <QVector>
#include <QJsonObject>
#include "../Entities/interlocutor.h"
#include "../Entities/message.h"
#include "../Entities/currentuser.h"

class ResponseParser
{
public:
    static CurrentUser parse_initialization_response(QByteArray response, QVector<Interlocutor>& result);
    static std::pair<Message, QString> parse_send_message_response(QJsonObject& message);
    static Message parse_new_message_response(QJsonObject& message);
    static Interlocutor parse_add_new_chat_response(QJsonObject& message);
private:
    static Interlocutor parse_interlocutor(QJsonObject interlocutor);
    static Message parse_message(QJsonObject message);
};

#endif // RESPONSEPARSER_H
