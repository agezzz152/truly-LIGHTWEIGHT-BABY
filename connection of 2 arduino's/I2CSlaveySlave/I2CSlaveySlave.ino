#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from peripheral device #8
  while (Wire.available()) { // peripheral may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
   if (c>=100){
  digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
  digitalWrite(LED_BUILTIN, LOW);
  }
 }
}
