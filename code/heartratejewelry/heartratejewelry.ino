/* Heart Rate Jewelry by Liz Corson 
 *  February 2016
 *  This code blinks or fades a WS2812 RGB LED at the user's heart rate.
 *  The LED changes color based on heart rate.
 */

/*  Based on:
 *   Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com
Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
 Also thanks to Scottie Digital for the fade code. http://buildinganledsuit.blogspot.com/p/fastled-pulse-of-color-and-then-fade.html
*/

/*
 * Wiring:
 * Pulse sensor purple: A0
 * LED data pin: 6
 */

#include "FastLED.h"
#include "RunningAverage.h"

//  Variables
int pulsePin = 0;     // Pulse Sensor purple wire connected to analog pin 0
int fadeAmount = 0;   // used to fade LED
int brightness = 0;
#define DATA_PIN 6    // pin for WS2812 LEDs
#define NUM_LEDS 6
CRGB leds[NUM_LEDS];
long lastBlinkTime = 0;
long lastFadeStartTime = 0;
long lastFadeIncrementTime = 0;
int fadeDelay = 15;
int beatlength = 0;
byte blinkFlag = 0;
byte fadeFlag = 0;
int avgBPM = 0;
int avgbeatlength = 0;
RunningAverage beatlengthlist(10);
RunningAverage BPMlist(10);

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 

void setup(){
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
  
  //set up RGB LEDs
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);

  //clear running averages
  beatlengthlist.clear();
  BPMlist.clear();
}

void loop(){
  
  serialOutput();       
    
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat

    //convert bpm to millisec per beat
    // (beats/min)^-1 * 60 s / min * 1000 ms/s
    beatlength = (int)(60.0*1000/BPM); //be sure to use a float to get the right number
                                      // then cast as int
    
    //Keep a running average of beat length and use that to fade or blink LED
    //Running average smooths noisy data
    BPMlist.addValue(BPM);
    beatlengthlist.addValue(beatlength);

    avgBPM = (int)BPMlist.getFastAverage();
    avgbeatlength = (int)beatlengthlist.getFastAverage();

    Serial.print("BPM: "); 
    Serial.print(BPM);
    Serial.print(" | Avg BPM: ");
    Serial.println(avgBPM);
    
    Serial.print("time per beat (ms): "); // can you access the variable BPM
    Serial.print(beatlength);
    Serial.print(" | Avg Beat Length: ");
    Serial.println(avgbeatlength);
    QS = false;                      // reset the Quantified Self flag for next time    
  }
  
  //Choose blink mode or fade mode by enabling one of these functions
  //ledBlinkToBeat();
  ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
}

// Use Avg BPM to determine color
void selectLEDColorByBPM() {
  int rval = 0;
  int gval = 0;
  int bval = 0;
  //select color
  if (avgBPM < 100) { // 0-99 Blue
    bval = 255;
  } else if (avgBPM < 120) { // 100 - 119 Green
    gval = 255;
  } else if (avgBPM < 140) { // 120 - 139 Yellow
    rval = 255;
    gval = 255;
  } else if (avgBPM < 160) { // 140 - 159 Orange
    rval = 255;
    gval = 110;
  } else { // 160+ Red
    rval = 255;
  }  
  for(int i = 0; i < NUM_LEDS; i++ ){
    leds[i].setRGB(rval,gval,bval);  
  }
}

//Blinks based on millis()-based "debouncing"
//Turn on LED at start time of beat and turn it off at half of beat time
void ledBlinkToBeat() {
  //if LED is off and it's been more than a beat length, turn on
  if(!blinkFlag && (unsigned long)(millis() - lastBlinkTime) > avgbeatlength) {    
    selectLEDColorByBPM();
    // turn on
    FastLED.show();
    lastBlinkTime = millis();
    blinkFlag = 1;
  }
  //if LED is on and the beat length is at least half over, turn off
  if (blinkFlag && (unsigned long)(millis() - lastBlinkTime) > avgbeatlength/2) {
    // turn off
    blinkFlag = 0;
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].setRGB(0,0,0);  
    }
    //leds[0] = CRGB::Black;
    FastLED.show();
  } 
}

// Fades based on millis()-based "debouncing"
// Keep LED on for 90% of beat length and fade according to heart rate
void ledFadeToBeat(){
  // if LED is off and it's time for a beat
  if(!fadeFlag && (unsigned long)(millis() - lastFadeStartTime) > avgbeatlength) {    
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
  } else if (fadeFlag && (unsigned long)(millis() - lastFadeStartTime) < avgbeatlength*9/10 && (unsigned long)(millis() - lastFadeIncrementTime) >= fadeDelay) {
    //do fade
    brightness = brightness + fadeAmount;
    brightness = constrain(brightness,0,255); 
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].fadeLightBy(brightness);  //fade by brightness. 0 = max light, 255 = min light
    }
    FastLED.show();
    //Serial.println(brightness); // make sure you're getting up to 255
    lastFadeIncrementTime = millis();
  }
  // if it's been more than 90% of a beat, turn LED off if it's on
  if (fadeFlag && (unsigned long)(millis() - lastFadeStartTime) > avgbeatlength*9/10) {
    // turn off
    fadeFlag = 0;
    for(int i = 0; i < NUM_LEDS; i++ ){
      leds[i].setRGB(0,0,0);  
    }
    FastLED.show();
  } 
}
