# heartratejewelry
A necklace that pulses RGB LEDs in time with your heart.

## Status
The main sketch (heartratejewelry) now has an option to blink or fade. I added a running average to smooth noisy sensor data. The LED changes color according to the measured heart rate. It now has 6 LEDs.

I've learned how to use OpenSCAD and have made a 3D model of the case that I plan to 3D print.

## Parts Used
- Frentaly Uno http://www.ebay.com/itm/321871945148
- Pulse sensor https://www.sparkfun.com/products/11574
- Addressable WS2812 RGB LEDs https://www.sparkfun.com/products/12986
- 100 μF capacitor https://www.sparkfun.com/products/96
- 220 Ω resistor

To be added in the future:
- Arduino Pro Mini https://www.sparkfun.com/products/11113
- LiPo charger/booster https://www.sparkfun.com/products/11231
- LiPo battery https://www.sparkfun.com/products/10718
- Neopixel Mini PCB https://www.adafruit.com/products/1612

## Libraries
FastLED https://github.com/FastLED/FastLED & PulseSensor https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino

## Photo
![alt tag](https://github.com/lizcorson/heartratejewelry/blob/master/photos/6 LEDs.jpg)
![alt tag](https://github.com/lizcorson/heartratejewelry/blob/master/photos/pulse led.jpg)
![alt tag](https://github.com/lizcorson/heartratejewelry/blob/master/case/heart model 4.PNG)