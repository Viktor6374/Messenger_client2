#include "message.h"

Message::Message(QString sender_username, QString message, QDateTime send_time) : QObject(){
    this->sender_username = sender_username;
    this->message = message;
    this->send_time = send_time;
}

Message::Message(const Message & other): QObject()
{
    sender_username = other.sender_username;
    message = other.message;
    send_time = other.send_time;
}

Message &Message::operator =(const Message & other)
{
    sender_username = other.sender_username;
    message = other.message;
    send_time = other.send_time;

    return *this;
}

QString Message::get_sender_username() {
    return sender_username;
}

QString Message::get_message() {
    return message;
}

QDateTime Message::get_send_time() {
    return send_time;
}

bool Message::operator>(const Message& other) const
{
    return send_time > other.send_time;
}

bool Message::operator<(const Message& other) const
{
    return send_time < other.send_time;
}


