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

long int currentT;
long int startT;

int resetPin = 7;


//IR lmao
int IRPins[] = { A8, A9, A10, A11, A12, A13, A14, A15 };
IRArray IRs(IRPins);


//LDRS lmao
int const LDR[] = { 15, 2, 4, 13, 12, 14 };         //from the rightest LDR clockwise, with esp
int LdrPins[NUM_LDR] = { A2, A3, A4, A5, A6, A7 };  //from the rightest LDR clockwise, with arduino connections
ldrArray LDRs(LdrPins);
bool isRetreating = 0;
double lAng = 0;

//motors lmao
int pwm[] = { 9, 12, 11, 10 };  //right up and clockwise
int in_1[] = { 30, 37, 35, 32 };
int in_2[] = { 31, 36, 34, 33 };
motors driver(pwm, in_1, in_2);


double ang, liniarSped, spinSped;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Serial.begin(9600);
  digitalWrite(resetPin, HIGH);


  //motors:
  driver.motorSetup();

  startT = millis();
  //neoPixel:
  strip.begin();
  strip.show();  // onWhiteLinee all pixels to 'off'
  strip.setBrightness(0);

  //Led for control
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(resetPin, OUTPUT);
}


void loop() {
  currentT = millis();
  colorWipe(strip.Color(0, 0, 0), 50);
  ang = 0;
  liniarSped = 125;
  spinSped = 0;

  ang = IRs.findBallAngle();
  // IRs.display();
  driver.moov(ang, liniarSped, spinSped);

  myDelay(20);

  if (currentT > startT + RESET_TIMER) {
    digitalWrite(resetPin, LOW);
  }


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


  // driver.moov(ang, liniarSped, spinSped);
  strip.show();
}





void displayVals() {
  int i;
  for (i = 0; i < NUM_LDR; i++) {
    Serial.print(LDRs.getVal_i(i));
    Serial.print(" - ");
  }
  Serial.print("| ");
  for (i = 0; i < NUM_LDR; i++) {
    if (LDRs.getStatus_i(i)) {
      Serial.print(i);
      Serial.print(", ");
    }
  }
  Serial.print(", ");
  Serial.print(LDRs.Angle());
  Serial.println(" |");

  //when an ldr is activated, change the first and last led in the closest neopixel strip to it.
  for (i = 0; i < NUM_LDR; i++) {
    if (LDRs.getStatus_i(i)) {
      strip.setPixelColor(i * 8, 100, 0, 50);
      strip.setPixelColor(i * 8 + 7, 100, 0, 50);
    }
  }
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
}
