#ifndef SERVICE_H
#define SERVICE_H
#include <QVector>
#include <QString>
#include <QMutex>
#include "../Entities/interlocutor.h"
#include "../Entities/currentuser.h"
#include "../connections/requestconnection.h"

class Service
{
public:
    Service(QVector<Interlocutor>& users, RequestConnection& connection, CurrentUser& current_user);
    bool add_new_chat(QString username);
    bool send_message(QString message_str);
    void set_answer_add_new_chat(Interlocutor& new_interlocutor);
    void set_answer_send_message(Message& message, QString& addressee);
    void set_new_message(Message& message);
    std::shared_ptr<Interlocutor> get_selected_interlocutor();
    Interlocutor get_interlocutor(int index);
    Interlocutor operator[](int index);
    int number_of_interlocutors();
    void set_selected_interlocutor(int index);
    void sort_users();
    ~Service();
private:
    QVector<Interlocutor> _users;
    std::shared_ptr<Interlocutor> _selected_interlocutor;
    RequestConnection _connection;
    bool _request_sent;
    CurrentUser _current_user;
    bool wait_response();
    Interlocutor * find_interlocutor_by_username(QString username);
    QMutex * mutex;
};

#endif // SERVICE_H
