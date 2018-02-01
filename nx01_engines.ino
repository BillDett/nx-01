#include <LEDFader.h>
#define LED_NUM 6

/*

  Enterprise NX-01 Bussard engine glow simulator.
  Using this excellent library: https://github.com/jgillick/arduino-LEDFader

*/

LEDFader leds[LED_NUM] = {
  LEDFader(3),
  LEDFader(5),
  LEDFader(6),
  LEDFader(9),
  LEDFader(10),
  LEDFader(11)
};

void setup() {
}

int thefloor = 10;
int mindelay = 500;
int maxdelay = 1500;

void loop() {
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
