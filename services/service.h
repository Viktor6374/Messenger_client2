#ifndef SERVICE_H
#define SERVICE_H
#include <QVector>
#include <QString>
#include <QMutex>
#include "../Entities/interlocutor.h"
#include "../Entities/currentuser.h"

class Service : public QObject
{
    Q_OBJECT
public:
    Service();
    Service(QVector<Interlocutor>& users, CurrentUser& current_user);

    std::shared_ptr<Interlocutor> get_selected_interlocutor();
    Interlocutor get_interlocutor(int index);
    Interlocutor operator[](int index);
    int number_of_interlocutors();
    void set_selected_interlocutor(int index);
    void sort_users();
    ~Service();

    void init(QVector<Interlocutor>& users, CurrentUser& current_user);
    bool add_new_chat(QString username);
    bool send_message(QString message_str);
signals:
    void change_filling();
    bool add_new_chat_request(QString username);
    bool send_message_request(Message message, QString addressee);
public slots:
    void set_answer_add_new_chat(Interlocutor new_interlocutor);
    void set_answer_send_message(Message message, QString addressee);
    void set_new_message(Message message);
private:
    QVector<Interlocutor> _users;
    std::shared_ptr<Interlocutor> _selected_interlocutor;
    bool _request_sent;
    CurrentUser _current_user;
    bool wait_response();
    Interlocutor * find_interlocutor_by_username(QString username);
};

#endif // SERVICE_H
