#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include "request.h"

namespace Morozov {
class Source{
public:
    Source();
    Source(int alpha, int beta, int sourcesAmount);

    Morozov::Request getNextRequest();

private:
    int alpha;
    int beta;
    int sourcesAmount;

    float *timesToWait;
    int *requestNumbers;

    void fillTimesToWait();
    std::pair<int, float> getMinTimeAndIndex();
    void removeMinTimeToWait();
};
}

#endif // SOURCE_H
