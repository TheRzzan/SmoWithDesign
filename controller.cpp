#include "controller.h"
#include "source.h"
#include "buffer.h"
#include "device.h"

Morozov::Controller::Controller()
{
    this->alpha = 0;
    this->beta = 0;
    this->lambda = 0;

    this->sourcesAmount = 0;
    this->buffersAmount = 0;
    this->devicesAmount = 0;

    this->requestsNumber = 0;
}

std::list<std::string> Morozov::Controller::modulateWork(Analytics &analytics)
{
    analytics.beginTransaction();
    analytics.config(sourcesAmount, buffersAmount, devicesAmount);

    std::list<std::string> resultList;

    Morozov::Source *sources = new Morozov::Source(alpha, beta, sourcesAmount);
    Morozov::Buffer *buffers = new Morozov::Buffer(buffersAmount);
    Morozov::Device *devices = new Morozov::Device(devicesAmount, lambda);

    float currentTime = 0;

    for (int i = 0; i < requestsNumber; i++) {
        Request nextRequest = sources->getNextRequest();
        currentTime += nextRequest.getTimeOfWait();

        std::list<std::pair<Request, int> > doneRequests = devices->freeDoneDevices(currentTime);
        if (doneRequests.size() > 0) {
            for (auto it = doneRequests.begin(); it != doneRequests.end(); ++it) {
                resultList.push_back("Девайс №" + std::to_string((*it).second) + " освободился в " + std::to_string((*it).first.getTimeOfWait()));
                analytics.removeRequestFromDevice((*it).first, (*it).second);

                if (!buffers->isEmptyBuff()) {
                    std::pair<Request, int> pair2 = buffers->getRequest();
                    Request request2 = pair2.first;
                    analytics.getRequestFromBuff(Request(
                                                     (*it).first.getTimeOfWait(),
                                                     request2.getSourceId(),
                                                     request2.getRequestNumber()),
                                                 pair2.second);

                    int deviceNum2 = devices->addNewRequest((*it).first.getTimeOfWait(), request2);
                    resultList.push_back("Заявка " + std::to_string(request2.getSourceId()) + "." + std::to_string(request2.getRequestNumber())
                                         + " загружена в девайс №" + std::to_string(deviceNum2));
                    analytics.addRequestToDevice(Request(
                                                     (*it).first.getTimeOfWait(),
                                                     request2.getSourceId(),
                                                     request2.getRequestNumber()),
                                                 (*it).second);
                }
            }
        }

        std::string tmpResStr = "Создана заявка " + std::to_string(nextRequest.getSourceId()) + "." + std::to_string(nextRequest.getRequestNumber());
        analytics.newRequestGenerate(Request(
                                         currentTime,
                                         nextRequest.getSourceId(),
                                         nextRequest.getRequestNumber()));
        if (!devices->isFreeDevice()) {
            if (buffers->isFreeBuff()) {
                int bufferNum = buffers->addNewRequest(nextRequest);
                tmpResStr += " и загружена в буффер №" + std::to_string(bufferNum + 1);
                analytics.addRequestToBuff(Request(
                                                 currentTime,
                                                 nextRequest.getSourceId(),
                                                 nextRequest.getRequestNumber()),
                                             bufferNum);
            } else {
                std::pair<Request, int> pair3 = buffers->deleteOldRequest();
                Request deletedRequest = pair3.first;
                resultList.push_back("Заявка " + std::to_string(deletedRequest.getSourceId()) + "." + std::to_string(deletedRequest.getRequestNumber())
                                     + " удалена из буффера.");
                analytics.removeRequestFromBuff(Request(
                                                 currentTime,
                                                 deletedRequest.getSourceId(),
                                                 deletedRequest.getRequestNumber()),
                                             pair3.second);
                int bufferNum = buffers->addNewRequest(nextRequest);
                tmpResStr += " и загружена в буффер №" + std::to_string(bufferNum);
                analytics.addRequestToBuff(Request(
                                                 currentTime,
                                                 nextRequest.getSourceId(),
                                                 nextRequest.getRequestNumber()),
                                             bufferNum);
            }
        } else {
            int deviceNum = devices->addNewRequest(currentTime, nextRequest);
            tmpResStr += " и загружена в девайс №" + std::to_string(deviceNum);
            analytics.addRequestToDevice(Request(
                                             currentTime,
                                             nextRequest.getSourceId(),
                                             nextRequest.getRequestNumber()),
                                         deviceNum);
        }

        resultList.push_back(tmpResStr);
    }

    analytics.commit(currentTime);
    return resultList;
}

void Morozov::Controller::setDevicesAmount(int value)
{
    devicesAmount = value;
}

void Morozov::Controller::setRequestsNumber(int value)
{
    requestsNumber = value;
}

void Morozov::Controller::setBuffersAmount(int value)
{
    buffersAmount = value;
}

void Morozov::Controller::setSourcesAmount(int value)
{
    sourcesAmount = value;
}

void Morozov::Controller::setLambda(int value)
{
    lambda = value;
}

void Morozov::Controller::setBeta(int value)
{
    beta = value;
}

void Morozov::Controller::setAlpha(int value)
{
    alpha = value;
}
