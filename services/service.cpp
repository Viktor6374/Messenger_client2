#include "service.h"
#include "../Threads/response_processing.h"

Service::Service(QVector<Interlocutor>& users, RequestConnection& connection, CurrentUser& current_user) :
    _users(users), _connection(connection), _current_user(current_user)
{
    _request_sent = false;
    _selected_interlocutor = nullptr;
    mutex = new QMutex();
}

bool Service::add_new_chat(QString username)
{
    QMutexLocker locker(mutex);
    _request_sent = true;
    _connection.addNewChat(username);

    return wait_response();
}

bool Service::send_message(QString message_str)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    QMutexLocker locker(mutex);
    Message message(_current_user.get_username(), message_str, currentDateTime);
    _request_sent = true;
    _connection.sendMessage(message, _selected_interlocutor->get_username());

    return wait_response();
}

bool Service::wait_response()
{
    Response_processing timeout;
    timeout.start();
    timeout.wait();

    QMutexLocker locker(mutex);
    if (_request_sent){
        _request_sent = false;
        return false;
    }

    return true;
}

Interlocutor& Service::get_interlocutor(int index)
{
    QMutexLocker locker(mutex);
    return _users[index];
}

Interlocutor& Service::operator[](int index)
{
    QMutexLocker locker(mutex);
    return _users[index];
}

int Service::number_of_interlocutors()
{
    QMutexLocker locker(mutex);
    return _users.size();
}

Interlocutor * Service::get_selected_interlocutor()
{
    QMutexLocker locker(mutex);
    return _selected_interlocutor;
}

void Service::set_selected_interlocutor(int index)
{
    QMutexLocker locker(mutex);
    Interlocutor user = _users[index];
    *_selected_interlocutor = user;
}


void Service::set_answer_add_new_chat(Interlocutor& new_interlocutor)
{
    QMutexLocker locker(mutex);
    _users.push_back(new_interlocutor);
    if (_request_sent){
        _request_sent = false;
    } else {
        _selected_interlocutor = _users.data() + _users.size() - 1;
    }
}

void Service::set_answer_send_message(Message& message, QString& addressee)
{
    QMutexLocker locker(mutex);
    Interlocutor * addr = find_interlocutor_by_username(addressee);
    addr->get_history_messaging().add_message(message);
    if (_request_sent){
        _request_sent = false;
    } else {
        addr->get_history_messaging().sort_messages();
    }

    sort_users();
}

void Service::set_new_message(Message& message)
{
    QMutexLocker locker(mutex);
    Interlocutor * addr = find_interlocutor_by_username(message.get_sender_username());
    addr->get_history_messaging().add_message(message);
    if (_request_sent){
        _request_sent = false;
    } else {
        addr->get_history_messaging().sort_messages();
    }

    sort_users();
}

Interlocutor * Service::find_interlocutor_by_username(QString username)
{
    QMutexLocker locker(mutex);
    for (int i = 0; i < _users.size(); i++){
        if (_users[i].get_username() == username){
            return _users.data() + i;
        }
    }

    return nullptr;
}

void Service::sort_users()
{
    QMutexLocker locker(mutex);
    QString username_selected = _selected_interlocutor->get_username();
    std::sort(_users.begin(), _users.end(), [](Interlocutor l, Interlocutor r){
        return l.get_history_messaging().get_first_message().get_send_time() <
               r.get_history_messaging().get_first_message().get_send_time();
    });
    _selected_interlocutor = find_interlocutor_by_username(username_selected);
}

Service::~Service()
{
    delete mutex;
    delete _selected_interlocutor;
}



