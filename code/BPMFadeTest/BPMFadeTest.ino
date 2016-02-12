/* Test fade timing and amount at user-set (not sensor) BPM. 
 * Use this sketch to tune color selection, fade update rate (fade delay),
 * LED-on time.
*/

#include "FastLED.h"
#define DATA_PIN 6
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
int BPM = 170;
int beatlength = 0;
byte fadeFlag = 0;
long lastFadeStartTime = 0;
long lastFadeIncrementTime = 0;
int fadeDelay = 15;
int fadeAmount = 0;
int brightness = 0;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {

  beatlength = (int)(60.0*1000/BPM); //be sure to use a float to get the right number
                                      // then cast as int
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  //delay(20);  
}
// Use BPM to determine color
void selectLEDColorByBPM() {
  int rval = 0;
  int gval = 0;
  int bval = 0;
  //select color
  if (BPM < 100) { // 0-99 Blue
    bval = 255;
  } else if (BPM < 120) { // 100 - 119 Green
    gval = 255;
  } else if (BPM < 140) { // 120 - 139 Yellow
    rval = 255;
    gval = 255;
  } else if (BPM < 160) { // 140 - 159 Orange
    rval = 255;
    gval = 110;
  } else { // 160+ Red
    rval = 255;
  }  
  for(int i = 0; i < NUM_LEDS; i++ ){
    leds[i].setRGB(rval,gval,bval);  
  }
}

//Fades based on millis()-based "debouncing"
void ledFadeToBeat(){
  // if LED is off and it's time for a beat
  if(!fadeFlag && (unsigned long)(millis() - lastFadeStartTime) > beatlength) {    
    selectLEDColorByBPM();
    brightness = 0;
    // turn on
    FastLED.show();
    lastFadeStartTime = millis();
    fadeFlag = 1;
    // Calculate fade amount. We want the LED on for 90% of the beat length.
    // Fade delay is set at 15. Find fade amount by max fade/([LED on time]/delay)
    // It will fade in bigger chunks for shorter beat length/higher BPM.
    fadeAmount = 255/(beatlength * 9/10 / fadeDelay);
  // if LED is on, it's in the 1st 90% of a beat, and it's been at least fadeDelay ms since an update to the LED
  // perform a fade and update LED
  } else if (fadeFlag && (unsigned long)(millis() - lastFadeStartTime) < beatlength*9/10 && (unsigned long)(millis() - lastFadeIncrementTime) >= fadeDelay) {
    //do fade
    brightness = brightness + fadeAmount;
    brightness = constrain(brightness,0,255); 
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].fadeLightBy(brightness);  //fade by brightness. 0 = max light, 255 = min light
    }
    FastLED.show();
    Serial.println(brightness); // make sure you're getting up to 255
    lastFadeIncrementTime = millis();
  }
  // if it's been more than 90% of a beat, turn LED off if it's on
  if (fadeFlag && (unsigned long)(millis() - lastFadeStartTime) > beatlength*9/10) {
    // turn off
    fadeFlag = 0;
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].setRGB(0,0,0);  
    }
    FastLED.show();
  } 
}
