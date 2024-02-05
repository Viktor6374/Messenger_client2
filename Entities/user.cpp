#include "user.h"

User::User(){}

User::User(QString username, QString first_name, QString second_name)
{
    this->username = username;
    this->first_name = first_name;
    this->second_name = second_name;
}

User::User(const User & other)
{
    this->username = other.username;
    this->first_name = other.first_name;
    this->second_name = other.second_name;
}

User & User::operator = (const User & other)
{
    this->username = other.username;
    this->first_name = other.first_name;
    this->second_name = other.second_name;

    return *this;
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

bool User::operator==(const User& other) const
{
    return username == other.username;
}

bool User::operator!=(const User& other) const
{
    return !(*this == other);
}

