#ifndef RESPONSE_PROCESSING_H
#define RESPONSE_PROCESSING_H

#include <QThread>

class Response_processing : public QThread
{
public:
    void run() override;
private:
    const unsigned long _waiting_response = 5000;
};

#endif // RESPONSE_PROCESSING_H
