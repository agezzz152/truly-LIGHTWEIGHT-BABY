#include <Adafruit_NeoPixel.h>
#include "ldrArray.h"
#include "parameters.h"


// int const LDR[] = { 15, 2, 4, 13, 12, 14 };  //from the rightest LDR clockwise, with esp connections
int LdrPins[NUM_LDR] = { A1, A2, A3, A4, A5, A6 };  //from the rightest LDR clockwise, with arduino connections
ldrArray LDRs(LdrPins);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(180);
}

void loop() {

  colorWipe(strip.Color(30, 30, 30), 50);
  //detects which ldrs are activated and detect someting bellow them.
  LDRs.CalcLineAngle();
  //prints ldr vals, the angle detected and the activated ldrs. also lights up neopixel near activaed ldr in purple
  displayVals();
  //update the neopixel strip
  strip.show();
}

int signOFx(int x) {
  return x / abs(x);
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
