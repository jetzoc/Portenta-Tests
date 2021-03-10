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
DigitalOut bit_zero(PJ_11, 1);  // D2 on Portenta
DigitalOut bit_one(PG_7, 1);    // D3
DigitalOut bit_two(PC_7, 1);    // D4 
DigitalOut bit_three(PC_6, 1);  // D5

DigitalOut bit_four(PA_8, 1);   // D6
DigitalOut bit_five(PI_0, 1);   // D7
DigitalOut bit_six(PC_3, 1);    // D8
DigitalOut bit_seven(PI_1, 1);  // D9

#define NUM_OF_CH 64         // sampling 64 channels
int mux_bits[NUM_OF_CH];        

/* Function prototype(s) */
void mbed_main(void ); 

/* Arduino code that runs once */ 
void setup() {

  /* Set up terminal access */ 
  Serial.begin(9600);
  
}

/* Arduino code that runs multiple times */ 
void loop() {

  mbed_main();

}

/* User-defined functions */ 
/* Timer ISR */ 
void timerISR(void )
{
  // Write to one GPIO pin and switch to next one in sequence
  
}

/* Main function for mbed platform */ 
void mbed_main(void )
{
  // Fill in mux bits 
  int sequence = 0x00; 
  for (int i = 0; i < NUM_OF_CH; i++)
  {
    mux_bits[i] = sequence; 
    sequence++; 
  }

  /* Testing out whether the array was filled in correctly */ 
  while (1) 
  {
    for (int i = 0; i < NUM_OF_CH; i++)
    {
      Serial.println( String(mux_bits[i]) ); 
    }
  }

  // Initialize a hardware timer
  Ticker tim;                   

  float tim_frq = 600;          // 600 Hz
  float timeout_us = ( (1 / tim_frq) * 1e6 );   // period = 1.67ms
  
  // Point hardware timer to a function once timeout (1,6666.6 us) is reached 
  tim.attach_us( &timerISR, timeout_us); 
  
  // Main loop for mbed platform 
  while(1) 
  {
    
  }

}

/*
 * Results:
 * - Timer interrupt rate @ 609.7 Hz
 * 
 * - Array verification pending... 
 */



