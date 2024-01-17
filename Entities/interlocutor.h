#ifndef INTERLOCUTOR_H
#define INTERLOCUTOR_H

#include "user.h"
#include "history_messaging.h"

class Interlocutor : public User
{
public:
    Interlocutor();
    Interlocutor(QString username, QString first_name, QString second_name);
    History_messaging& get_history_messaging();
private:
    History_messaging history;
};

#endif // INTERLOCUTOR_H
