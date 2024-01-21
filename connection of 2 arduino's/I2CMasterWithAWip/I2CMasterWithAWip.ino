#include <Wire.h>

void setup() {
  Wire.begin(8);                 // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  int val;
  requestEvent(val);
}
void requestEvent(int val) {
  val = analogRead(A0);
  Wire.write(val);  //print the value to serial
}
