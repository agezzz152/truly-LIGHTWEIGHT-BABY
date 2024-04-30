#include "PixyCam.h"
#include <Pixy2.h>


PixyCam pixy;

void setup() {
  Serial.begin(115200);
}

void loop() {
  pixy.UpdateData();
  Serial.print("Distance: ");
  Serial.print(pixy.GetDistance());
  Serial.print(" Angle: ");
  Serial.println(pixy.GetAngle());
  delay(200);
}
