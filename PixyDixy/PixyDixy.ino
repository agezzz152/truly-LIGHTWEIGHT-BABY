#include "PixyCam.h"
#include <Pixy2.h>


PixyCam pixy;

void setup() {
  Serial.begin(115200);
}

void loop() {
  pixy.UpdateData();
  int goal = pixy.getGoal();
  Serial.print("Distance: ");
  Serial.print(pixy.GetDistance(goal));
  Serial.print(" Angle: ");
  Serial.println(pixy.GetAngle(goal));
  delay(200);
}
