#ifndef HISTORY_MESSAGING_H
#define HISTORY_MESSAGING_H

#include <vector>
#include "message.h"

class History_messaging
{
public:
    History_messaging();
    void add_message(Message& message);
    void clear();
    Message get_next_message();
    Message get_first_message();
private:
    std::vector<Message> messages;
    int current_message;
};

#endif // HISTORY_MESSAGING_H
