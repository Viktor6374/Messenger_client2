#ifndef USER_H
#define USER_H
#include <QString>


class User
{
protected:
    User(QString username, QString first_name, QString second_name);
public:
    QString get_username();
    QString get_first_name();
    QString get_second_name();
private:
    QString username;
    QString first_name;
    QString second_name;
};

#endif // USER_H
