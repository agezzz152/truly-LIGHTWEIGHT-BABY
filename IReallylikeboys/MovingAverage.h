#ifndef __MOVING_AVERAGE__
#define __MOVING_AVERAGE__
#define num_array 20

class MovingAverage {
private:
    int dataArray[num_array];
    int sizeOfDataArray = num_array;
    int count;
public:
    MovingAverage();
    float updateData(float value);
    void reset(void);
};

#endif
