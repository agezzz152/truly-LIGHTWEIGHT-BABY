#ifndef __MOVING_AVERAGE__
#define __MOVING_AVERAGE__
#include "parameters.h"

class MovingAverage {
private:
    int dataArray[num_array];
    int sizeOfDataArray = num_array;
    int count = 0;
public:
    MovingAverage() {}
    float updateData(float value);
    void reset(void);
};

#endif
