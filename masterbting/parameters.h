//*****parameters.h*****//
/*
This file contains all the defines, and parametes for our robot.
We put here all the variables so it'll be extra easy to change each on them
(no need to search where we put that parameter).
*/

#ifndef __PARAMETERS__
#define __PARAMETERS__
#include <math.h>
#include <Arduino.h>

//motors//
#define NUM_MOTORS 4  //The number of motors that are in use

//Neopixel//
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip
#define NEO_PIN 5      // Define the pin you're using to control the Neopixels

//LDRs//
// Define the value that if an ldr returns a val higher then this, it's officialy activated
#define CAP_VALUE 800
#define NUM_LDR 6
// How many ms the robot will retreat if encountered a white line
#define RETREAT_DELAY 50

//IRs//
#define NUM_IR 8
// Any IR that returns higher than 100 is not detecting any ball and we cap the IR there
#define IRCAP 100
// A parameter that fixed the ball angle calculated by the IR
#define ANGLE_FIX 30
// Defines how many spaces from the lowest val IR we want to include in our calculation
#define NUM_SPACES_FROM_CLOSEST_IR 1

//Mooving Avg//
#define num_array 5  //how many objects will be needed to calc in the moving average

//Reset Button//
#define RESET_TIMER 5000  //dictates the time between the arduino resetting itself (in ms)

//Pixy//
#define OwnGoal 0    //index for own goal
#define EnemyGoal 1  //index for enemy goal

#endif