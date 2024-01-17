#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include "user.h"

class CurrentUser : public User
{
public:
    CurrentUser(QString username, QString first_name, QString second_name);
};

#endif // CURRENTUSER_H
