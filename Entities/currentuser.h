#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include "user.h"

class CurrentUser : public User
{
public:
    CurrentUser(QString username, QString first_name, QString second_name, QString _password);
    CurrentUser(QString username, QString first_name, QString second_name);
    CurrentUser();
    CurrentUser(const CurrentUser & other) = default;
    CurrentUser & operator = (const CurrentUser & other) = default;
    QString get_password();
private:
    QString _password;
};

#endif // CURRENTUSER_H
