#include <Adafruit_NeoPixel.h>

#define PIN 5 // Define the pin you're using to control the Neopixels
#define NUM_PIXELS    32  // Define the number of Neopixels in your strip
#define Delay 200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(100);
  // Set all Neopixels to red
  colorWipe(strip.Color(30, 0, 0), 50);  // Red color with a 50ms delay

}

void loop() {
  //Disco();
  colorWipe(strip.Color(30, 0, 0), 50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
  void Disco(){
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, (50,0,0));
      strip.setPixelColor(i-1, (0, 50, 0));
      strip.setPixelColor(i-2, (0, 0, 50));


      strip.show();
      delay(Delay);
    }
  }
