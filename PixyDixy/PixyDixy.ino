#include "PixyCam.h"
#include <Pixy2.h>


PixyCam pixy;

void setup() {
  Serial.begin(115200);
}

void loop() {
  pixy.UpdateData();
  int goal = pixy.getGoal();
  if (goal == 0) {
    Serial.print("Blue: ");
  }
  else if (goal == 1) {
    Serial.print("Yellow: ");
  }
  Serial.print("Distance: ");
  Serial.print(pixy.GetDistance(goal));
  Serial.print(" Angle: ");
  Serial.println(pixy.GetAngle(goal));
  delay(200);
}
