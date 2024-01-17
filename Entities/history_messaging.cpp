#include "history_messaging.h"

History_messaging::History_messaging()
{
    current_message = 0;
}

void History_messaging::add_message(Message& message)
{
    messages.push_back(message);
}

void History_messaging::clear()
{
    messages.clear();
    current_message = 0;
}

Message History_messaging::get_next_message()
{
    if (current_message == messages.size()){
        throw std::exception("the previous message was the last one");
    }

    return messages[current_message++];
}

Message History_messaging::get_first_message()
{
    current_message = 0;
    return get_next_message();
}
