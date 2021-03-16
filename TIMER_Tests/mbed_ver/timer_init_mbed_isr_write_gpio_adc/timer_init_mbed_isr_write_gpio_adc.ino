/* 
 * Goals: 
 * 1. To initialize a hardware timer on 
 *    the Portenta H7 using the mbed 
 *    C++ API/libraries 
 * 
 * 2. To use write to 8 pins via an interrupt
 *      - a sequence of numbers from 0 to 63 (0x00 to 0x3F)
 * 
 * 3. To sample the ADC channel (input)
 *      - read the input
 *      - store the input somewhere
 *
 * Hardware: 
 *  - D2-D9 (eight pins): digital outputs for a bus write of 8 bits
 *  - A0 : analog input to ADC
 *  - Connect AREF to 3.3V for a more stable ADC reference voltage
 *
 * Notes:
 *  - Written using Mbed API within an Arduino sketch
 *  - Pins D2 and D3 hold bits 7 (MSB) and 8 respectively. 
 *    - These two pins stay at 0 (low) because the span of 0x00 to 0x3F
 *      does not occupy these bits. 
 * 
 * Repo link: 
 * https://github.com/jetzoc/Portenta-Tests
 * 
 * March 10, 2021
 */

#include "mbed.h"
using namespace mbed;


/*** Globals ****/ 
// Create a pin array (reversed)
#define BYTE_SIZE 8 
int eeg_bus[BYTE_SIZE] = { 9, 8, 7, 6, 5, 4, 3, 2};

// Create an array for holding information to send to a multiplexer
// and a channel tracker for the 64 different writes to pin array
#define NUM_OF_CH 64         // sampling 64 channels
int mux_bits[NUM_OF_CH];        
int current_ch = 0; 

// Create an array for ADC samples 
#define ADC_IN A0
int adc_samples[NUM_OF_CH];


/*** Function prototype(s) ***/
void mbed_new_main(void ); 


/**** Arduino code that runs once ****/ 
void setup() {

  // Set up terminal access 
  //Serial.begin(9600);

  // Set up eight digital pins as output for information 
  pinMode(2, OUTPUT);  // bit 7
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);  // bit 4

  pinMode(6, OUTPUT);  // bit 3
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);  // bit 0

  // Set up ADC input 
  pinMode(ADC_IN, INPUT); 

  // Timing pin output 
  pinMode(0, OUTPUT); // time the ISR
  
}


/*** Arduino code that runs multiple times ***/ 
void loop() {

  mbed_new_main();

}


/*** User-defined functions ***/ 
/** Timer ISR **/ 
 void timerISR(void )
 {
   digitalWrite(0, HIGH); 

    // Cycles for number of channels to read
    for (current_ch = 0; current_ch < NUM_OF_CH; current_ch++) 
    {
      // Cycles for number of bits to send (i.e. 8 bits)
      // Write to one byte to a GPIO pin and switch to next one in the bus
      // e.g. Bit 0 is written to pin 0 in the bus (array of pins) and so on...
      for (int bit_num = 0; bit_num < BYTE_SIZE; bit_num++) 
      {
        digitalWrite(eeg_bus[bit_num], bitRead(mux_bits[current_ch], bit_num));
      }

      // Sample ADC now
      adc_samples[current_ch] = digitalRead(ADC_IN); 

    }

}


/*** Main function for mbed platform ***/ 
void mbed_new_main(void )
{
  // Fill in mux bits 
  for (int sequence = 0; sequence < NUM_OF_CH; sequence++)
  {
    mux_bits[sequence] = sequence; 
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
    digitalWrite(0, LOW); 
   
  } // end while loop

}


/**************************************************
 * Results:
 * - Timer interrupt rate @ 600 Hz
 *
 * - Using the timer interrupt: Each pin frequency (bit 7 - 0)
 *    - D9: 19,189 Hz         
 *    - D8: 9,609 Hz               
 *    - D7: 4,804 Hz
 *    - D6: 2,401 Hz
 *
 *    - D5: 1,201 Hz
 *    - D4: 600 Hz
 *    - D3: 0 Hz (bit not needed)
 *    - D2: 0 Hz (bit not needed) 
 *
 * - ISR timing: 100 us
 ************************************************/
