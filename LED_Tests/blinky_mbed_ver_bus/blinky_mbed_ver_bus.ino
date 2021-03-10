/* 
 * Goals: 
 * 1. To write to three LEDs using the BusOut interface 
 *    using the Mbed libraries.
 * 
 * Hardware: 
 *  - LED1 (red) or PK5
 *  - LED2 (green) or PK6
 *  - LED3 (blue) or PK7
 *
 * Notes:
 * Written using Mbed API within an Arduino sketch
 * 
 * Repo link: 
 * https://github.com/jetzoc/Portenta-Tests
 * 
 * March 10, 2021
 */

#include "mbed.h"
using namespace mbed;
using namespace rtos::ThisThread;

/* Function prototype(s) */
void mbed_main(void ); 

/* Arduino code that runs once */ 
void setup() {
  
}

/* Arduino code that runs multiple times */ 
void loop() {

  mbed_main();

}

/* Main function for mbed platform */ 
void mbed_main(void )
{
  // Using BusOut interface to combine/group three DigitalOut pins (LEDs)
  // in order to write to them at once
  // Order of pins is reversed to byte order
  BusOut three_leds(LED1, LED2, LED3); 

  // Set the lights to tinkle 
  // Main loop for mbed platform 
  while(1) 
  {
    for (int i = 0; i < 8; i++)       // 8 because 2^3
    {
      three_leds = i; 

      sleep_for(500);                // wait for 500 ms
    }
    
  }

}




