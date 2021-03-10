/* 
 * Goals: 
 * 1. To write to eight pins using the BusOut interface 
 *    using the Mbed libraries. 
 * 2. Time how long it takes
 *
 * Hardware: 
 *  - PA8 or D6  (Ch. 1)
 *      - one of the eight output pins in the bus
 *  - PK1 or D1  (Ch. 2)
 *      - timing pin 
 *  - D2-D9 (eight pins)
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

/* Globals */ 
// Using BusOut interface to combine 8 DigitalOut pins 
// in order to write to all at the same time.
// Order of pins reversed to bit order. (Endianness reversed)
BusOut output_bus (PI_1, PC_3, PI_0, PA_8, PC_6, PC_7, PG_7, PJ_11); 

// Above replaces all of this... 
// DigitalOut bit_zero(PJ_11, 1);  // D2 on Portenta
// DigitalOut bit_one(PG_7, 1);    // D3
// DigitalOut bit_two(PC_7, 1);    // D4 
// DigitalOut bit_three(PC_6, 1);  // D5

// DigitalOut bit_four(PA_8, 1);   // D6
// DigitalOut bit_five(PI_0, 1);   // D7
// DigitalOut bit_six(PC_3, 1);    // D8
// DigitalOut bit_seven(PI_1, 1);  // D9  

/* Function prototype(s) */
void mbed_main(void ); 

/* Arduino code that runs once */ 
void setup() {

  /* Set up terminal access */ 
  //Serial.begin(9600);
  
}

/* Arduino code that runs multiple times */ 
void loop() {

  mbed_main();

}

/* Main function for mbed platform */ 
void mbed_main(void )
{  
  // Setting up the timing pin
  DigitalOut tim_pin(PK_1, 0);    // ensures pin starts deasserted

  // Main loop for mbed platform 
  while(1) 
  {
    // Assert timing pin
    tim_pin = 1; 
    
    // Writing to the bus 
    output_bus = 0x3F;      // 0xFF all pins HIGH (another option to write to pins)

    // De-assert timing pin
    tim_pin = 0; 
    
  }

}

/* Results: 
 *  - All bus pins around ~3.2V when writing 0xFF
 *  - Bus pins measured [0, 0, 3.2, 3.2; 3.2, 3.2, 3.2, 3.2] V DC, respectively, when writing 0x3F
 *  - tim_pin measures 2.2 us when digital pins are used in a bus
 */





