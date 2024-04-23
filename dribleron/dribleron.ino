#include "parameters.h"
#include "dribler.h"

int dribPins[4] = {28, 29, 4, 22}; //in1, in2, pwm, HBRIDGEMODE in arduino
dribler MyDrip(dribPins);


void setup() {
  Serial.begin(9600);
  MyDrip.dribSetup();
}


void loop() {
  MyDrip.Drip(HIGH);
  delay(10);
}
