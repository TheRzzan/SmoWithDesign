#include "source.h"
#include <QApplication>

Morozov::Source::Source()
{
    this->alpha = 0;
    this->beta = 0;
    this->sourcesAmount = 0;

    this->timesToWait = new float[this->sourcesAmount];
    this->requestNumbers = new int[this->sourcesAmount];
}

Morozov::Source::Source(int alpha, int beta, int sourcesAmount)
{
    this->alpha = alpha;
    this->beta = beta;
    this->sourcesAmount = sourcesAmount;

    this->timesToWait = new float[sourcesAmount];
    this->requestNumbers = new int[sourcesAmount];

    for (int i = 0; i < sourcesAmount; i++) {
        this->requestNumbers[i] = 0;
        this->timesToWait[i] = -1;
    }
}

Morozov::Request Morozov::Source::getNextRequest()
{
    fillTimesToWait();
    std::pair<int, float> min = getMinTimeAndIndex();
    removeMinTimeToWait();
    return Request(min.second, min.first + 1, requestNumbers[min.first]);
}

void Morozov::Source::fillTimesToWait()
{
    for (int i = 0; i < sourcesAmount; i++) {
        if (timesToWait[i] <= 0) {
            requestNumbers[i]++;
            timesToWait[i] = ((float)qrand()/(float)RAND_MAX)*(beta - alpha) + alpha;
        }
    }
}

std::pair<int, float> Morozov::Source::getMinTimeAndIndex()
{
    std::pair<int, float> min = std::make_pair(0, timesToWait[0]);
    for (int i = 0; i < sourcesAmount; i++) {
        if (timesToWait[i] < min.second) {
            min = std::make_pair(i, timesToWait[i]);
        }
    }

    return min;
}

void Morozov::Source::removeMinTimeToWait()
{
    std::pair<int, float> min = getMinTimeAndIndex();
    for (int i = 0; i < sourcesAmount; i++) {
        timesToWait[i] -= min.second;
    }
}
