#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QString>

class Message : public QObject
{
    Q_OBJECT
public:
    Message(QString sender_username, QString message, QDateTime send_time);
    Message(const Message &);
    Message & operator =(const Message & other);
    QString get_sender_username();
    QString get_message();
    QDateTime get_send_time();
    bool operator>(const Message& other) const;
    bool operator<(const Message& other) const;
private:
    QString sender_username;
    QString message;
    QDateTime send_time;
};

#endif // MESSAGE_H
