/* 
 * Goals: 
 * 1. To initialize a hardware timer on 
 *    the Portenta H7 using the mbed 
 *    C++ API/libraries 
 * 
 * 2. To use write to 8 pins via an interrupt
 *      - a sequence of numbers from 0 to 63 (0x00 to 0x3F)
 * 
 * Hardware: 
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
BusOut eeg_bus (PI_1, PC_3, PI_0, PA_8, PC_6, PC_7, PG_7, PJ_11); 
int current_ch = 0; 

#define NUM_OF_CH 64         // sampling 64 channels
int mux_bits[NUM_OF_CH];        

/* Function prototype(s) */
void mbed_new_main(void ); 

/* Arduino code that runs once */ 
void setup() {

  /* Set up terminal access */ 
  Serial.begin(9600);
  
}

/* Arduino code that runs multiple times */ 
void loop() {

  mbed_new_main();

}

/* User-defined functions */ 
/* Timer ISR */ 
// void timerISR(void )
// {
//   // Write to one GPIO pin and switch to next one in sequence
//   eeg_bus = mux_bits[current_ch]
//   current_ch++;

//   // Reset current_ch only when last channel is read
//   if (current_ch == (NUM_OF_CH - 1))   // if current ch == 63
//   {
//     current_ch = 0; 
//   }
// }

/* Main function for mbed platform */ 
void mbed_new_main(void )
{
  // Fill in mux bits 
  for (int sequence = 0; sequence < NUM_OF_CH; sequence++)
  {
    mux_bits[sequence] = sequence; 
  }

  // // Initialize a hardware timer
  // Ticker tim;                   

  // float tim_frq = 600;          // 600 Hz
  // float timeout_us = ( (1 / tim_frq) * 1e6 );   // period = 1.67ms
  
  // // Point hardware timer to a function once timeout (1,6666.6 us) is reached 
  // tim.attach_us( &timerISR, timeout_us); 
  
  // Main loop for mbed platform 
  while(1) 
  {
    for (int i = 0; i < NUM_OF_CH; i++)
    {
      Serial.println( String(mux_bits[i]) ); 
    }
  }

}

/*
 * Results:
 * - Timer interrupt rate @ 609.7 Hz
 * - Array verification = done!
 */



