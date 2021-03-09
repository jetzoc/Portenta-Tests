/* 
 * Goal: 
 * To initialize a STM32 hardware timer 
 * on board the Portenta H7 using the mbed 
 * C++ API/libraries
 * 
 * Hardware: 
 *  - PA8 on STM32 MCU or D6 on Portenta Board 
 *    - GPIO which serves to verify timer frequency
 *
 * Notes:
 * Written using Mbed API within an Arduino sketch
 * 
 * Repo link: 
 * https://github.com/jetzoc/Portenta-Tests
 * 
 * March 9, 2021
 */

#include "mbed.h"
using namespace mbed;

/* Globals */ 
DigitalOut timeoutPin(PA_8);  // initialize PA8 (aka. D6)

/* Function prototype(s) */
void mbed_main(void ); 
void togl(DigitalOut &_pin); 

/* Arduino code that runs once */ 
void setup() {

  /* Set up terminal access */ 
  //Serial.begin(9600);
  
}

/* Arduino code that runs multiple times */ 
void loop() {

  mbed_main();

}

/* User-defined functions */ 
void togl(DigitalOut &_pin)
{
  _pin = !_pin;
}

void timerISR(void)
{
  togl(timeoutPin);
}

/* Main function for mbed platform */ 
void mbed_main(void )
{
  Ticker tim;                   // initialize a hardware timer

  timeoutPin = 1;               // set PA8 high initially

  float tim_frq = 600;          // 600 Hz
  float timeout_us = ( (1 / tim_frq) * 1e6 );   // period = 1.67ms
  
  /* Point hardware timer to a function once timeout (1,6666.6 us) is reached */ 
  tim.attach_us( &timerISR, timeout_us); 
  
  /* Main loop for mbed platform */
  while(1) 
  {
    //Testing out if we can toggle pin independent of timer ISR 
    //togl(timeoutPin); 

    //Testing out whether math is correct for timer freq. 
    //Serial.println( "timeout: " + String(timeout_us, 2) );     // arduino printing; uncomment Serial.begin in setup()
  
  }
}
/*
 * Results:
 * Timer timeouts every 1.64 ms or at a rate of 609.7 Hz
 */