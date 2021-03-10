/* 
 * Goals: 
 * 1. To write to one pin using the BusOut interface 
 *    using the Mbed libraries.
 * 2. Time how long it takes
 *
 * Hardware: 
 *  - PA8 or D6  (Ch. 1)
 *      - output pin
 *  - PI0 or D7  (Ch. 2)
 *      - timing pin 
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
  // Using BusOut interface to group just one Digital pin
  //BusOut gpio_pin(PA_8);

  // Using no bus interface to write to just one Digital pin
  DigitalOut gpio_pin(PA_8); 

  // Setting up the timing pin
  DigitalOut tim_pin(PI_0, 0);    // ensures pin starts deasserted

  // Main loop for mbed platform 
  while(1) 
  {
    // Assert timing pin
    tim_pin = 1; 
    
    // Write to gpio output
    gpio_pin = 0x01;

    // De-assert timing pin
    tim_pin = 0; 
    
  }

}

/* Results: 
 *  - gpio_pin around ~3.2V DC
 *  - tim_pin measures 1.5 us when digital pin is used in a bus
 *  - tim_pin measures 240 ns when digital pin is used without a bus
 */



