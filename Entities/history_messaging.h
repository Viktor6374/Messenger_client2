#ifndef HISTORY_MESSAGING_H
#define HISTORY_MESSAGING_H

#include <vector>
#include <QMutex>
#include "message.h"

class History_messaging
{
public:
    History_messaging();
    void add_message(Message message);
    void clear();
    Message get_next_message();
    Message get_first_message();
    void reset_counter();
    int get_quantity_messages();
    void sort_messages();
    ~History_messaging();
private:
    std::vector<Message> messages;
    int current_message;
    QMutex * mutex;
};

#endif // HISTORY_MESSAGING_H
