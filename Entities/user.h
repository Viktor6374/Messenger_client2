#ifndef USER_H
#define USER_H
#include <QString>


class User
{
protected:
    User();
    User(QString username, QString first_name, QString second_name);
public:
    QString get_username();
    QString get_first_name();
    QString get_second_name();
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
protected:
    QString username;
    QString first_name;
    QString second_name;
};

#endif // USER_H
