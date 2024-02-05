#include "service.h"
#include "../Threads/response_processing.h"

Service::Service(QVector<Interlocutor>& users, CurrentUser& current_user) :
    _users(users), _current_user(current_user)
{
    _request_sent = false;

}

void Service::init(QVector<Interlocutor>& users, CurrentUser& current_user)
{
    _users = users;
    _current_user = current_user;
}

Service::Service(){}

bool Service::add_new_chat(QString username)
{
    _request_sent = true;
    add_new_chat_request(username);

    return wait_response();
}

bool Service::send_message(QString message_str)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    Message message(_current_user.get_username(), message_str, currentDateTime);

    _request_sent = true;

    send_message_request(message, _selected_interlocutor->get_username());

    return wait_response();
}

bool Service::wait_response()
{
//    Response_processing timeout;
//    timeout.start();
//    timeout.wait();

    if (_request_sent){
        _request_sent = false;
        return false;
    }

    return true;
}

Interlocutor Service::get_interlocutor(int index)
{
    return _users[index];
}

Interlocutor Service::operator[](int index)
{
    return _users[index];
}

int Service::number_of_interlocutors()
{
    return _users.size();
}

std::shared_ptr<Interlocutor> Service::get_selected_interlocutor()
{
    Interlocutor user = find_interlocutor_by_username(_selected_interlocutor->get_username());
    std::shared_ptr<Interlocutor> result = std::make_shared<Interlocutor>(user);
    return result;
}

void Service::set_selected_interlocutor(int index)
{
    Interlocutor user = _users[index];
    _selected_interlocutor = std::make_shared<Interlocutor>(user);
    change_filling();
}


void Service::set_answer_add_new_chat(Interlocutor new_interlocutor)
{
    qDebug() << "2";
    _users.push_back(new_interlocutor);
    if (_request_sent){
        _request_sent = false;
    } else {
        _selected_interlocutor = std::make_shared<Interlocutor>(_users[_users.size() - 1]);
    }

    change_filling();
}

void Service::set_answer_send_message(Message message, QString addressee)
{
    Interlocutor * addr = find_interlocutor_by_username(addressee);

    if (addr == nullptr){
        throw std::logic_error("Incorrect username (incorrect format file)");
    }

    addr->get_history_messaging().add_message(message);
    if (_request_sent){
        _request_sent = false;
    } else {
        addr->get_history_messaging().sort_messages();
    }

    sort_users();
    change_filling();
}

void Service::set_new_message(Message message)
{
    Interlocutor * addr = find_interlocutor_by_username(message.get_sender_username());

    if (addr == nullptr){
        throw std::logic_error("Incorrect username (incorrect format file)");
    }

    addr->get_history_messaging().add_message(message);
    if (_request_sent){
        _request_sent = false;
    } else {
        addr->get_history_messaging().sort_messages();
    }

    sort_users();
    change_filling();
}

Interlocutor * Service::find_interlocutor_by_username(QString username)
{
    for (int i = 0; i < _users.size(); i++){
        if (_users[i].get_username() == username){
            return _users.data() + i;
        }
    }

    return nullptr;
}

void Service::sort_users()
{
    std::sort(_users.begin(), _users.end(), [](Interlocutor l, Interlocutor r){
        return l.get_history_messaging().get_first_message().get_send_time() <
               r.get_history_messaging().get_first_message().get_send_time();
    });
}

Service::~Service()
{
}



