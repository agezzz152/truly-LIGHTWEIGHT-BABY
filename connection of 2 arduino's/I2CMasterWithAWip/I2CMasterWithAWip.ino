#include <Wire.h>

void setup() {
  Wire.begin(8);                 // join i2c bus with address #8
  Wire.onRequest(requestEvent);  // register event
}

void loop() {
  int val;
  val = analogRead(A0);  //connect grayscale sensor to Analog 0
  requestEvent(val);
}
void requestEvent(int val) {
  Wire.write(val);  //print the value to serial
}
