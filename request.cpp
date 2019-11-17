#include "request.h"

Morozov::Request::Request()
{
    this->timeOfWait = 0.0;
    this->sourceId = 0;
    this->requestNumber = 0;
}

Morozov::Request::Request(float timeOfWait, int sourceId, int requestNumber)
{
    this->timeOfWait = timeOfWait;
    this->sourceId = sourceId;
    this->requestNumber = requestNumber;
}

float Morozov::Request::getTimeOfWait() const
{
    return timeOfWait;
}

int Morozov::Request::getSourceId() const
{
    return sourceId;
}

int Morozov::Request::getRequestNumber() const
{
    return requestNumber;
}
