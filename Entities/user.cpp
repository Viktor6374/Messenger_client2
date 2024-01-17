#include "user.h"

User::User(QString username, QString first_name, QString second_name)
{
    this->username = username;
    this->first_name = first_name;
    this->second_name = second_name;
}

QString User::get_username() {
    return username;
}

QString User::get_first_name() {
    return first_name;
}

QString User::get_second_name() {
    return second_name;
}
