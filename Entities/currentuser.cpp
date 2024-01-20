#include "currentuser.h"

CurrentUser::CurrentUser(QString username, QString first_name, QString second_name, QString password) : User(username, first_name, second_name)
{
    _password = password;
}

QString CurrentUser::get_password()
{
    return _password;
}
