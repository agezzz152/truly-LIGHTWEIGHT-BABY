#ifndef __MOVING_AVERAGE__
#define __MOVING_AVERAGE__

class MovingAverage {
private:
    float *dataArray;
    int sizeOfDataArray;
    int count;
public:
    MovingAverage(int num_array);
    float updateData(float value);
    void reset(void);
};

#endif
