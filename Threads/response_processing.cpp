#include "response_processing.h"

void Response_processing::run()
{
    this->msleep(_waiting_response);
}
