# heartratejewelry
A necklace that pulses RGB LEDs in time with your heart.

## Status
The main sketch (heartratejewelry) now has an option to blink or fade. I added a running average to smooth noisy sensor data. The LED changes color according to the measured heart rate. So far I have only tested this with a single LED, but it should work for multiple LEDs as long as NUM_LEDs is set appropriately. All delays have been removed and now everything operates off millis() counters.

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

## Libraries
FastLED https://github.com/FastLED/FastLED & PulseSensor https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino

## Photo
![alt tag](https://github.com/lizcorson/heartratejewelry/blob/master/photos/pulse led.jpg)