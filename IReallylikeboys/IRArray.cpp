#include "IRArray.h"

/*
a function so that shellSortKnuth will know what a assending order is, with IRSensor types
If we were sorting an array of ints, we wouldn't need this func
but cause we are sorting an array of IRSensors, the function doesn't know which one is bigger
*/
bool lessThen(IRSensor &a, IRSensor &b) {
  return (a.GetValue() < b.GetValue());
}

/*a and b should both be between 0 to 359 (angles in degrees)
this function returns the average between the two angles (also between 0 and 359)
*/
float avgAngs(float &a, float &b) {
  float avg = (a + b) / 2;
  if (avg >= 360)
    avg = avg - 360;
  return avg;
}

//initiates the sensors array to include the correct pins and indexes
IRArray::IRArray(int *pins) {
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i] = IRSensor(pins[i], i);
  }
}

//only updates the values stored in the sensors array and returns nothingg
void IRArray::readVals() {
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i].updateValue();
    if (sensors[i].GetValue() > IRCAP)
      sensors[i].SetVal(IRCAP);
  }
}

//read vals and then returns the minimum index of the min Value from the sensors array
int IRArray::LowestIR() {
  int minVal = IRCAP, minIndex = 0;
  for (int i = 0; i < NUM_IR; i++) {
    sensors[i].updateValue();
    if (sensors[i].GetValue() < minVal) {
      minVal = sensors[i].GetValue();
      minIndex = i;
    }
  }
  return minIndex;
}


//returns the average value of all of the sensors' values
float IRArray::avgIRVal() {
  int sum = 0;
  for (int i = 0; i < NUM_IR; i++) {
    sum += sensors[i].GetValue();
  }
  return sum / NUM_IR;
}



//the main function that finds the ball angle using the date from IR sensors
float IRArray::findBallAngle() {
  readVals();
  //create an array of the same sensors and same vals but we are going to manipulate it
  IRSensor sensorsManipulated[NUM_IR];
  for (int i = 0; i < NUM_IR; i++) {
    sensorsManipulated[i] = sensors[i];
  }

  //sort the new sensors array
  shellSortKnuth(sensorsManipulated, NUM_IR, lessThen);

  float closestAng = sensorsManipulated[0].GetAngle();
  float closestVal = sensorsManipulated[0].GetValue();
  int i = 0;
  float secClosestAng;
  float secClosestVal;
  int secIndex;
  
  secIndex = sensorsManipulated[i].getIndex();

  do {
    i++;
    secIndex = sensorsManipulated[i].getIndex();
  } while (abs(secIndex - sensorsManipulated[0].getIndex()) > NUM_SPACES_FROM_CLOSEST_IR && abs(secIndex - sensorsManipulated[0].getIndex()) != NUM_IR - 1) ;

  secClosestAng = sensorsManipulated[i].GetAngle();
  secClosestVal = sensorsManipulated[i].GetValue();

  //if the two angles have a huge gap between them, they are 315 and 0 in that order
  if ((closestAng - secClosestAng) > 250)
    secClosestAng += 360;
  //if the two angles have a minus huge gap between them, they are 0 and 315 in that order
  else if ((closestAng - secClosestAng) < -250)
    secClosestAng -= 360;

  /*
  You want the ballAngle to be closestAng + corrections.
  corrections will be how the difference between closest angles, 
  times how different their values are squared so that if they are far, it'll matter less.
  If they both have the same val, then closestVal / secClosestVal = 1 and the whole angle is the average between the two.
  devision by 2 is neccecery so that when vals are equal, the ang will be the average
  desmos link to demonstrate with some vals: https://www.desmos.com/calculator/3jouqeacbo
  */
  ballAngle = closestAng + (secClosestAng - closestAng) / 2 * pow((closestVal / secClosestVal), 2);
  if (ballAngle > 360)
    ballAngle -= 360;
  if (ballAngle < 0)
    ballAngle += 360;

  return ballAngle;
}


void IRArray::display() {
  for (int i = 0; i < NUM_IR; i++) {
    Serial.print(sensors[i].GetValue());
    Serial.print(" | ");
  }
  Serial.print("Angle: ");
  Serial.println(ballAngle);
}


void IRArray::CalculateAngle() {
  readVals();
  IRSensor sensorsManipulated[NUM_IR];
  for (int i = 0; i < NUM_IR; i++) {
    sensorsManipulated[i] = sensors[i];
  }

  shellSortKnuth(sensorsManipulated, NUM_IR, lessThen);
  
  IRSensor closest = sensorsManipulated[0];
  IRSensor SecClosest = sensorsManipulated[1];
  float closestAng = closest.GetAngle();
  float secClosestAng = SecClosest.GetAngle();
  //if the two angles have a huge gap between them, they are 315 and 0 in that order
  if ((closestAng - secClosestAng) > 250)
    secClosestAng += 360;
  //if the two angles have a minus huge gap between them, they are 0 and 315 in that order
  else if ((closestAng - secClosestAng) < -250)
    secClosestAng -= 360;
  //float angle = avgAngs(closestAng, secClosestAng);
  float angle = closestAng;
  ballAngle = angle; 
}

float IRArray::getBallAngle() {
  return ballAngle;
}