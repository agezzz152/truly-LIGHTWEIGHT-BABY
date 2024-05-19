#include "motors.h"

int signOfX(const int &x) { 
  return x / abs(x); //returns 1 if the argument was positive and -1 if negative
}

void myDelay(int millDelay) {
  int startTime = millis(); // saves the time that the function started
  //Serial.print("StartTime: ");
  //Serial.println(startTime);
  int currentT;
  while (true) {
    currentT = millis(); //saves the current time.
    //Serial.print("CurrentT: ");
    //Serial.println(currentT);
    if (currentT >= startTime + millDelay) { // If the current time >= the time the func started + the given delay, the loop ends, the func stops, and the code continues. Else, thw loop continues until the condition is met.
      break;
    }
  }
}


motors::motors(int *pwm, int *in1, int *in2) { //Recieves an arry of pwm pins, in1 and in2 pins of each motor.
  for (int i = 0; i < NUM_MOTORS; i++) {
    wheels[i] = wheel(pwm[i], in1[i], in2[i], i); //gives each wheel it's suitable pin values and index
  }

  digitalWrite(2, LOW); //HBMODE. For the motor driver.
  digitalWrite(3, LOW);
}


void motors::motorSetup() {
  for (int i = 0; i < NUM_MOTORS; i++) { //Sets pinMode to output for each pin in each wheel.
    wheels[i].wheelSetup();
  }
}

void motors::simpleMotorTest(int a, int b) { //First argument is the index of the motor to test. The second is the index + 1 of the motor, but it's defualt is 4 which means that every motor after that.
  //For Clock wise motion , in_1 = High , in_2 = Low

  for (int i = a; i < b; i++) { // Turns the motor cw with pwm of 100
    wheels[i].writeIN1(HIGH);
    wheels[i].writeIN2(LOW);
    wheels[i].writePWM(100);
  }

  myDelay(1000); //Wait 1 second

  for (int i = a; i < b; i++) { // Turns the motor ccw with pwm of 100
    wheels[i].writeIN1(LOW);
    wheels[i].writeIN2(HIGH);
  }

  myDelay(1000); // Wait 1 second
}


void motors::moovMultiDirSimple() {
  moov(0, 0, 100); //Move farwrad for half a second
  myDelay(500);
  moov(180, 100, 0); //Move backward for half a second
  myDelay(500);
  moov(90, 100, 0); //Move right for half a second
  myDelay(500);
  moov(270, 100, 0); //Move left for half a second
  myDelay(500);
}

void motors::BasicAngleMooving(const double &ang, const double &liniarSped, const double &spinSped) {
  if (ang <= 45 || ang >= 315) // if angle is between 315 and 45 degrees, then the angle is 0.
    moov(0, liniarSped, spinSped); 
  else if (ang >= 45 && ang <= 135) // if angle is between 45 and 135 degrees, then the angle is 90.
    moov(90, liniarSped, spinSped);
  else if (ang >= 135 && ang <= 225) // if angle is between 135 and 225 degrees, then the angle is 180.
    moov(180, liniarSped, spinSped);
  else if (ang >= 225 && ang <= 315) // if angle is between 225 and 315 degrees, then the angle is 270.
    moov(270, liniarSped, spinSped);
}


/* function moves the robot in a certien angle. 
angle = angle between dribler and chosen angle of movement,
sped = linear speed,
speen = circular speed. */
void motors::moov(double dirAngle, const double &sped, const double &speen) { // Calculates the desired angle, speed, and spin, and then using trigonometry, calculates the pwm and direction of each motor.
  //angle in a number betwin 0 and 2pi, sped in a number betwin 0 and 255, and speen is a number betwin 0 and 255
  int i;
  //turning the angle from degrees to rad
  dirAngle = dirAngle / (180) * (3.141592653589793);

  //if not inputed for the robot to stop
  if (!(sped == 0) || !(speen == 0)) {


    speedPart = (abs(sped)) / (abs(sped) + abs(speen));
    speenPart = 1 - speedPart;

    /* adding the reguler forward, beckward, left, right movment
    rad45 = 45 degrees in rads */

    pwmVal[0] = -sin(rad45 - dirAngle) * sped * speedPart;  //right front
    pwmVal[1] = -sin(rad45 + dirAngle) * sped * speedPart;  //right back
    pwmVal[2] = sin(rad45 - dirAngle) * sped * speedPart;   //left back
    pwmVal[3] = sin(rad45 + dirAngle) * sped * speedPart;   //left front


    // adding the circular motion for the motors
    for (i = 0; i < 4; i++) {
      pwmVal[i] = pwmVal[i] + (speen * speenPart);

      if (pwmVal[i] > 250) {
        pwmVal[i] = 250;
      }
      if (pwmVal[i] < -250) {

        pwmVal[i] = -250;
      }
      wheels[i].writePWM(abs(pwmVal[i]));

      wheels[i].writeIN1((signOfX(pwmVal[i]) + 1) / 2);
      wheels[i].writeIN2(1 - ((signOfX(pwmVal[i]) + 1) / 2));
    }
  }
}