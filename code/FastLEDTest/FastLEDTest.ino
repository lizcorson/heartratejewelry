#include "FastLED.h"
#define DATA_PIN 6
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
void setup() { 
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  FastLED.setBrightness(64);
  
  // Turn the first led red for 1 second
  //leds[0] = CRGB::HotPink; 
  leds[0].setRGB(214, 2, 112);
  FastLED.show();
  delay(1000);

  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
  
  //leds[0] = CRGB::HotPink; 
  leds[0] = CRGB::Purple;
  FastLED.show();
  delay(1000);

  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);

  leds[0].setRGB( 0, 56,  168);
  FastLED.show();
  delay(1000);

  // Set the first led back to black for 1 second
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}
