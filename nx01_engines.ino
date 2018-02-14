#include <LEDFader.h>
#define LED_NUM 6

/*

  Enterprise NX-01 Bussard engine glow simulator.
  Using this excellent library: https://github.com/jgillick/arduino-LEDFader

  Also drives the navigation lights blinking.

  // TODO: Can/should we drive engine pulsing as well with "DIY" PWM on a digital pin?

*/

LEDFader leds[LED_NUM] = {
  LEDFader(3),
  LEDFader(5),
  LEDFader(6),
  LEDFader(9),
  LEDFader(10),
  LEDFader(11)
};

int navLED = 13;
long navLast;
unsigned long navStart;
unsigned long navEnd;
long navOn = 1.48 * 1000;
long navOff = 0.90 * 1000;
int navValue = HIGH;

int strobeLED = 8;
unsigned long strobeStart;
unsigned long strobeEnd;
long strobeOn = 0.25 * 1000;
long strobeOff = 1.25 * 1000;
int strobeValue = HIGH;

void setup() {
    navStart = millis();
    navEnd = navStart + navOn;
    pinMode(navLED, OUTPUT);
    strobeStart = millis();
    strobeEnd = strobeStart + strobeOn;
    pinMode(strobeLED, OUTPUT);}


int thefloor = 10;
int mindelay = 500;
int maxdelay = 1500;

void loop() {

  unsigned long now = millis();

  // Blink the Navigation Lights
  if ( now < navEnd ) {
    digitalWrite(navLED, navValue);   
  } else {
    navStart = millis();
    if ( navValue == HIGH ) {
      navEnd = navStart + navOff;
      navValue = LOW;
    } else {
      navValue = HIGH;
      navEnd = navStart + navOn;
    }
  }

  
   // Blink the Strobe Lights
  if ( now < strobeEnd ) {
    digitalWrite(strobeLED, strobeValue);   
  } else {
    strobeStart = millis();
    if ( strobeValue == HIGH ) {
      strobeEnd = strobeStart + strobeOff;
      strobeValue = LOW;
    } else {
      strobeValue = HIGH;
      strobeEnd = strobeStart + strobeOn;
    }
  } 
  
   // Update all LEDs and start new fades if any are done
  for (byte i = 0; i < LED_NUM; i++) {
    LEDFader *led = &leds[i];
    led->update();
 
    // This LED is not fading, start a new fade
    if (led->is_fading() == false) {
      int duration = random(mindelay, maxdelay);
 
      // Fade Up
      if (led->get_value() == thefloor) {
        byte intensity = random(10, 255);
        led->fade(intensity, duration);
      }
      // Fade Down
      else {
        led->fade(thefloor, duration);
      }
    }
  }  
}
