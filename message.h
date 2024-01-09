#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <string>

class Message
{
public:
    Message(std::string sender_username, std::string message, std::time_t send_time);
    std::string get_sender_username();
    std::string get_message();
    std::time_t get_send_time();
private:
    std::string sender_username;
    std::string message;
    std::time_t send_time;
};

#endif // MESSAGE_H
