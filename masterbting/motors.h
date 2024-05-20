//*****motors.h*****//
/*
This class allows us to group all our motors into a simple array 
that contains all their parameters nicely.
Also, allows us to create multiple moving (and testing) functions (even if we only use one of them at the end!)
and "hide" them tidly in this two files.
*/

#ifndef __MOTORS__
#define __MOTORS__
#include <Arduino.h>
#include "parameters.h"
#include "wheel.h"

int signOfX(const int &x);    //returns 1 if the argument was positive and -1 if negative
void myDelay(int millDelay);  // A delay we made because the delay() function was buggy and unreliable

class motors {
private:
  wheel wheels[NUM_MOTORS];  // Creates an array with the given number (4)
  double pwmVal[4] = { 0 };  // Creates an array for the pwm values for each motor
  double speedPart;          // Variable that sets the speed of the robot
  double speenPart;          // Varibale that sets the spin of the robot (0 - now spin, 0 < - spin)
  double rad45 = 0.785398;   // 45 Degrees in rad


public:
  motors(int *pwm, int *in1, int *in2);  //Recieves an array of pwm, in1, and in2. Each array contains the pins of each motor.

  void motorSetup();  //Does WheelSetup() for every wheel.

  void moov(double dirAngle, const double &sped, const double &speen);  //Only god knows how it works (you give it a direction in degrees, a speed, and if you want, spin)

  void moovMultiDirSimple();  // Uses moov() to go forward, delay, backward, delay, right, delay, left, delay.

  void simpleMotorTest(int a = 0, int b = NUM_MOTORS);  // Give it the number of motor that you want to test - 1 and depending on you need you can give it the number of motor or more (if you want motor1 to work, you write (0,1). If you want motor1 and 2, you write (0, 2))

  void BasicAngleMooving(const double &ang, const double &liniarSped, const double &spinSped);  // tells the robot to move in 8 possible directions. depending on the angle, it will round it up to the closest angle that is a multiply of 45 degrees.
};


#endif