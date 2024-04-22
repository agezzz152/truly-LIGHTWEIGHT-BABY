#include "ldrArray.h"

ldrArray::ldrArray(int *pins) {
  for (int i = 0; i < NUM_LDR; i++) {
    LDR[i] = ldrSensor(pins[i], i);
  }
}

int ldrArray::getVal_i(int index) {
  return LDR[index].getVal();
}

bool ldrArray::getStatus_i(int index) {
  return LDR[index].getStatus();
}


void ldrArray::ReadAllLDR() {
  for (int i = 0; i < NUM_LDR; i++) {
    LDR[i].read();
  }
}


double ldrArray::CalcLineAngle() {
  int sumAng = 0;
  NActiveLDR = 0;
  for (int i = 0; i < NUM_LDR; i++) {
    if (LDR[i].read()) {
      //for each activated ldt, add the of it to the sum of angles.
      sumAng += LDR[i].getAngle();
      NActiveLDR++;
    }
  }
  if (NActiveLDR > 0) {
    //make an average angle for all the ldr detecting a white line
    angle = (sumAng / NActiveLDR);
  } else {
    //if not detected a line, return -1.
    angle = -1;
  }
  return angle;
}