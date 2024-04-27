
#include "MovingAverage.h"
#include "IRArray.h"
#include "parameters.h"

int IRPins[] = { A7, A8, A9, A10, A11, A12, A13, A14 };
MovingAverage IR[NUM_IR];

IRArray IRs(IRPins);
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  IRs.findBallAngle();
  IRs.display();
}