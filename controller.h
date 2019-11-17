#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <string>
#include "analytics.h"

namespace Morozov {
class Controller
{
public:
    Controller();

    std::list<std::string> modulateWork(Analytics &analytics);

    void setAlpha(int value);
    void setBeta(int value);
    void setLambda(int value);

    void setSourcesAmount(int value);
    void setBuffersAmount(int value);
    void setDevicesAmount(int value);

    void setRequestsNumber(int value);

private:
    int alpha;
    int beta;
    int lambda;

    int sourcesAmount;
    int buffersAmount;
    int devicesAmount;

    int requestsNumber;
};
}

#endif // CONTROLLER_H
