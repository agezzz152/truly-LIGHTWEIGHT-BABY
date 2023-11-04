#include <Adafruit_NeoPixel.h>

#define PIN 5
#define LEDNUM 32
#define delayval 50
#define photores 34
Adafruit_NeoPixel pixels(LEDNUM, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.setBrightness(100);
  pixels.begin();
  Serial.begin(115200);
  pixels.setBrightness(150);
  delay(200);
}

void loop() {
  LightUp();
  int reading = analogRead(photores);
  Serial.println(reading);
  delay(delayval);
}


void LightUp() {
  for (int j = 0; j < LEDNUM; j++){
    pixels.setPixelColor(j, pixels.Color(0,0,30));
    }
    pixels.show();
}

void LightOff() { 
  pixels.clear();
  pixels.show();
}
