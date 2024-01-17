#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H
#include <QVector>
#include <QJsonObject>
#include "../Entities/interlocutor.h"
#include "../Entities/message.h"

class ResponseParser
{
public:
    static QVector<Interlocutor> parse_initialization_response(QByteArray response);
private:
    static Interlocutor parse_interlocutor(QJsonObject interlocutor);
    static Message& parse_message(QJsonObject message);
};

#endif // RESPONSEPARSER_H
