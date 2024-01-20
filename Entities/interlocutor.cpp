#include "interlocutor.h"

Interlocutor::Interlocutor() : User()
{

}

Interlocutor::Interlocutor(QString username, QString first_name, QString second_name) : User(username, first_name, second_name)
{

}

History_messaging& Interlocutor::get_history_messaging()
{
    return history;
}
