#ifndef __PARAMETERS__
#define __PARAMETERS__
#include <math.h>
#include <Arduino.h>

//motors
#define NUM_MOTORS 4

//Neopixel
#define NUM_PIXELS 48  // Define the number of Neopixels in your strip
#define NEO_PIN 5          // Define the pin you're using to control the Neopixels

//LDRs
#define CAP_VALUE 800
#define NUM_LDR 6
#define RETREAT_DELAY 50

//IRs
#define NUM_IR 8
#define IRCAP 100
#define ANGLE_FIX 30
#define NUM_SPACES_FROM_CLOSEST_IR 1

//Mooving Avg
#define num_array 5

//Reset Button
#define RESET_TIMER 5000



#endif