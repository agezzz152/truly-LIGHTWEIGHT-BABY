#include "MovingAverage.h"


MovingAverage::MovingAverage(int num_array) {
    dataArray = new float[num_array];
    sizeOfDataArray = num_array;
    count = 0;
}

float MovingAverage::updateData(float value) {
    count++;
    if (count >= sizeOfDataArray) count = 0;
    dataArray[count] = value;
 
    float rslt = 0;
    for (int i = 0; i < sizeOfDataArray; ++i) {
        rslt += dataArray[i];
    }
    
    return rslt / sizeOfDataArray;
}

void MovingAverage::reset(void) {
    for (int i = 0; i < sizeOfDataArray; ++i) {
        dataArray[i] = 0;
    }
}
