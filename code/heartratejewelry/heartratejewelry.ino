
/*  Pulse Sensor Amped 1.4    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ---------------------- 
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md   
 ----------------------       ----------------------  ----------------------
*/

#include "FastLED.h"

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 12;                // pin to blink led at each beat
int fadePin = 5;                // pin to blink led at each beat
int fadeAmount = 5;                 // used to fade LED on with PWM on fadePin
int brightness = 0;
#define DATA_PIN 6
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
long lastBlinkTime = 0;
int beatlength = 0;
byte blinkFlag = 0;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 


void setup(){
  //pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  //pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE, 
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
//   analogReference(EXTERNAL);
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);   
  FastLED.setBrightness(64);
}


//  Where the Magic Happens
void loop(){
  
  serialOutput();       
    
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        
    //serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
    Serial.print("hi your bpm is "); // can you access the variable BPM
    Serial.println(BPM);
    
    // use BPM to calculate blink & fade rate
    
    //convert bpm to millisec per beat
    // (beats/min)^-1 * 60 s / min * 1000 ms/s
    beatlength = (int)(60.0*1000/BPM);
    
    //Plan: keep a running average of beat length and use that to fade or blink LED
    
    Serial.print("time per beat (ms): "); // can you access the variable BPM
    Serial.println(beatlength);
    QS = false;                      // reset the Quantified Self flag for next time    
  }
  ledBlinkToBeat();
  //ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
  delay(20);                             //  take a break
}



void ledBlinkToBeat() {
  if(!blinkFlag && (unsigned long)(millis() - lastBlinkTime) > beatlength) {
    // turn on
    //leds[0].setRGB(0, 0, 255);

    //select color
    if (BPM < 100) {
      leds[0] = CRGB::Blue;
    } else if (BPM < 120) {
      leds[0] = CRGB::Green;
    } else if (BPM < 140) {
      leds[0] = CRGB::Yellow;
    } else if (BPM < 160) {
      leds[0] = CRGB::Orange;
    } else {
      leds[0] = CRGB::Red;
    }  
    FastLED.show();
    lastBlinkTime = millis();
    blinkFlag = 1;
  }
  if (blinkFlag && (unsigned long)(millis() - lastBlinkTime) > beatlength/2) {
    // turn off
    blinkFlag = 0;
    leds[0] = CRGB::Black;
    FastLED.show();
  }
  
  
  
  
}

void ledFadeToBeat(){

}




