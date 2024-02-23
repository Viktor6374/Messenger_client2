#include "history_messaging.h"

History_messaging::History_messaging()
{
    current_message = 0;
    mutex = new QMutex();
}

History_messaging::History_messaging(const History_messaging & other)
{
//    qDebug() << "messages before" << other.messages.size();
    messages = std::vector<Message>(other.messages);
//    qDebug() << "messages after" << messages.size();
    current_message = 0;
    mutex = new QMutex();
}

History_messaging & History_messaging::operator = (const History_messaging & other)
{
    messages = std::vector<Message>(other.messages);

    return *this;
}

void History_messaging::add_message(Message message)
{
    QMutexLocker locker(mutex);
    messages.push_back(message);
}

void History_messaging::clear()
{
    QMutexLocker locker(mutex);
    messages.clear();
    current_message = 0;
}

Message History_messaging::get_next_message()
{
    QMutexLocker locker(mutex);
    if (current_message == messages.size()){
        throw std::logic_error("The previous message was the last one");
    }

    return messages[current_message++];
}

Message History_messaging::get_first_message()
{
    QMutexLocker locker(mutex);
    if (messages.size() == 0){
        throw std::logic_error("The message list is empty");
    }
    return messages[0];
}

void History_messaging::reset_counter()
{
    QMutexLocker locker(mutex);
    current_message = 0;
}

int History_messaging::get_quantity_messages()
{
    QMutexLocker locker(mutex);
    return messages.size();
}

void History_messaging::sort_messages()
{
    QMutexLocker locker(mutex);
    std::sort(messages.begin(), messages.end());
}

History_messaging::~History_messaging()
{
}


