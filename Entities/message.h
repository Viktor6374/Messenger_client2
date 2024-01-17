#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QString>

class Message
{
public:
    Message(QString sender_username, QString message, QDateTime send_time);
    QString get_sender_username();
    QString get_message();
    QDateTime get_send_time();
private:
    QString sender_username;
    QString message;
    QDateTime send_time;
};

#endif // MESSAGE_H
