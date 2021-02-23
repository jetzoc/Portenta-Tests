/*    
 *  DAC input and output test for the Portenta board
 *   - 12 bit resolution
 *   - Writes a software generated square signal to DAC
 *   - Has AREF pin connected to 3.3V
 *   
 *  Hardware set-up: 
 *  A6 = analog output from DAC 
 *  D0 = digital output for timing purposes (scope ch. 2)
 *  D1 = digital output to see generated square signal from DAC (scope ch. 1)
 * 
 *  For schematic and notes see: https://github.com/jetzoc/Portenta_Tests.git
 *  
 *  February 22, 2021
 */
#include <stdlib.h>

void setup() {
  /* DAC @ 12-bits */
  analogWriteResolution(12);

  /* Set up the DAC output pin */
  pinMode(DAC, OUTPUT);   // pin A6 (analog); another name for A6 is DAC

  /* Set up a digital pin as an output to toggle it (for timing purposes) */
  pinMode(0, OUTPUT);     // pin D0

  /* Set up another digital pin to see the conversion back to digital (from the analog DAC pin) */
  pinMode(1, OUTPUT);     // pin D1
  
  /* Serial terminal baud rate (if needed) */
  Serial.begin(9600);

  Serial.println("*** DAC test on Portenta Board: Digital Wave Creation ***");

}

void loop() {

  /* Toggle a digital pin before reading */
  digitalWrite(0, HIGH);
  
  /* Write a values to the DAC pin */  
  for (int i = 0; i < 20; i++) {   // low signal
    int val = 0; 
    analogWrite(DAC, val); 
    digitalWrite(1, val); 
  }

  for (int i = 0; i < 20; i++) {  // high signal
    int val = 1; 
    analogWrite(DAC, val); 
    digitalWrite(1, val); 
  }
  
  /* Toggle digital pin again */
  digitalWrite(0, LOW);

}

/*
 * RESULTS:
 *  deltaT = 88.00 us
 *  # of writes = 40
 *  
 *  delta T for 1 write = 88.00 us / 40 = 2.2 us
 */
