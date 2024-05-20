// When we started to work on this code, only us and god understood it.
// Now, only god understands it.
// In order to warn others from this code, please update the counter accordingly:
// Hours watsted on stupid mistakes ( = aka this code): 13
#include <Adafruit_NeoPixel.h>
#include "motors.h"
#include "parameters.h"
#include "ldrArray.h"
#include "MovingAverage.h"
#include "IRArray.h"

#include "PixyCam.h"


long int currentT;
long int startT;

int resetPin = 7;


//IR lmao
int IRPins[] = { A8, A9, A10, A11, A12, A13, A14, A15 }; // the array of the pins of the IR sensors
IRArray IRs(IRPins); // Setting up the IR sensor and array.


//LDRS lmao
//int const LDR[] = { 15, 2, 4, 13, 12, 14 };         //from the rightest LDR clockwise, with esp
int LdrPins[NUM_LDR] = { A2, A3, A4, A5, A6, A7 };  //from the rightest LDR clockwise, with arduino connections
ldrArray LDRs(LdrPins); // Setting up LDR pins and array
bool isRetreating = 0; //if TRUE, we execute Retreat, to avoid white line
double lAng = 0; // The angle of the detected White line

//motors lmao
int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
int in_1[] = { 30, 37, 35, 32 };
int in_2[] = { 31, 36, 34, 33 };
motors driver(pwm, in_1, in_2); // Initiate the motors with thier pins.


double ang, liniarSped, spinSped; // Variable for the moov function that controls the robot's movement.

PixyCam pixy; // initiate pixy
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800); // initiate the neopixel

void setup() {
  // Serial.begin(9600);
  digitalWrite(resetPin, HIGH); // This pin is connected to the reset button so it must be on. If it's off, the Arduino will be stuck in a reset loop.


  //motors:
  driver.motorSetup(); // Sets up the motors, determines the pinMode and values.

  startT = millis(); // saves the time in milliseconds
  //neoPixel:
  strip.begin(); // Starts the neopixels.
  strip.show();  // onWhiteLinee all pixels to 'off'
  strip.setBrightness(0);

  //Led for control
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(resetPin, OUTPUT);
}


void loop() {
  currentT = millis(); // saves the time loop() started in milliseconds
  colorWipe(strip.Color(0, 0, 0), 50); // sets the neopixels color to none.
  ang = 0; // direction of the robot is straight 
  liniarSped = 125; // the speed of the robot is half of it's full capabilities, but we don't want him to drive so fast for several reasons.
  spinSped = 0; // the robot does not spin while he drives.

  
  //if you want robot to chase ball: 
  /*
  ang = IRs.findBallAngle(); // sets the angle that the robot goes in, as the direction of the ball, according to the IR sensors.
  // IRs.display(); // shows the IR values and angle.
  driver.moov(ang, liniarSped, spinSped); // Moving the robot with wanted speed and spin, and the angle of the robot.

  myDelay(20); // delay of 20 milliseconds

  if (currentT > startT + RESET_TIMER) { // If the time the loop has started is grater than the start time by the selected time for a reset
    digitalWrite(resetPin, LOW); // Reset the arduino.
  }
  */


  // spinSped = liniarSped / (180 * 180) * ang * (360 - ang);
  // if (ang >= 180) {
  //   spinSped = -spinSped;
  // }0
  // if (ang > 20 && ang <= 180)
  //   spinSped = 50;
  // else if (ang > 180 && ang < 340)
  //   spinSped = -50;
  // else
  //  spinSped = 0;


  //if you want robot to move strait and avoid white lines:
  /*
   driver.moov(ang, liniarSped, spinSped); // the robot drives according to the insructions we set up in the start of the loop

  
  colorWipe(strip.Color(100, 100, 100), 50); // sets the neopixels to white.
  
  if (!LDRs.getIsRetreating()) { // if not during the proccess of retreating from a white line
    finds out which ldrs are active
    calc the angle of the ldrs detected and store in global variable
   LDRs.CalcLineAngle(); //checks the values of the LDRs. If 1 or more sensors detect a white line, then the isRetreating value is 1.
   driver.moov(ang, liniarSped, spinSped); // Continue to drive
  }

  //function for checking if we are in the middle of a retreat
  LDRs.handleRetreat(driver, ang + 180, liniarSped * 2, spinSped); // If the robot is in a retreating state, it moves the robot in the opposite angle of the white line, and the robot drives x2 the speed.

  //displayVals(); // displays the value of the LDR sensors, the sensors that detected a white line, and the angle
  */

  
  //if you want the robot to moov back and forth only if you can see the enemy goal
   /*



 // This function is trash and doesn't even work. There is no need to spend time commenting on this code. Better to work on more essential things first.
  pixy.UpdateData(); // gets data from the camera
  driver.moov(0, 0, 40); // the robot spins.
  int goal = pixy.getGoal();
    if (pixy.GetAngle(EnemyGoal) >= -10 && pixy.GetAngle(EnemyGoal <= 10) ) {
      driver.moov(0, 100, 0);
      myDelay(2000);
      driver.moov(180, 50, 0);
      myDelay(2000);
    }
  strip.show();
  */
}






void displayVals() {
  int i;
  for (i = 0; i < NUM_LDR; i++) { // Prints the value of each LDR
    Serial.print(LDRs.getVal_i(i));
    Serial.print(" - ");
  }
  Serial.print("| ");
  for (i = 0; i < NUM_LDR; i++) { // If an LDR detects a white line, it will add his index to the list of detected LDRs
    if (LDRs.getStatus_i(i)) {
      Serial.print(i);
      Serial.print(", ");
    }
  }
  Serial.print(", ");
  Serial.print(LDRs.Angle()); // Prints the angle of the white line, if there is.
  Serial.println(" |");

  //when an ldr is activated, change the first and last led in the closest neopixel strip to it.
  for (i = 0; i < NUM_LDR; i++) {
    if (LDRs.getStatus_i(i)) {
      strip.setPixelColor(i * 8, 100, 0, 50); // if an LDR detects a while line, the first and last LED of his neo pixel will change the color to purple. That way we have a visual indication of the detection of the LDR.
      strip.setPixelColor(i * 8 + 7, 100, 0, 50);
    }
  }
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) { // sets the color of the NEOPIXEL strip.
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color); 
  }
}
