/*    
 *  DAC input test for the Portenta board
 *   - 12 bit resolution
 *   - Uses a software generated signal that outputs the full 12-bit range of DAC
 *   - Has AREF pin connected to 3.3V
 *   
 *  Hardware set-up: 
 *  A6 = analog output from DAC (scope ch. 2)
 *  D0 = digital output for timing purposes (scope ch. 1)
 * 
 *  For schematic and notes see: https://github.com/jetzoc/Portenta-Tests.git
 *  
 *  February 22, 2021
 */

#include <stdlib.h>

void setup() {
  /* DAC @ 12-bits */
  analogWriteResolution(12);

  /* Set up the DAC output pin 
   * This pin is probed on oscilloscope */
  pinMode(DAC, OUTPUT);   // pin A6 (analog)

  /* Set up a digital pin as an output to toggle it (for timing purposes) */
  pinMode(0, OUTPUT);     // pin D0
  
  /* Serial terminal baud rate (if needed) */
  Serial.begin(9600);

  Serial.println("*** DAC test on Portenta Board ***");

}

void loop() {

  /* Toggle digital pin before writing */
  digitalWrite(0, HIGH);
  
  /* Write multiple values to the DAC pin */
  for (int val = 0; val <= 4096 ; val +=32) // loops 128x
  {  
    analogWrite(DAC, val);   // writing to A6
    //Serial.println(val); 

  } 
  
  /* Toggle digital pin after writings */
  digitalWrite(0, LOW);

}

/* RESULTS: 
 *  deltaT = 244 us / 128 writes = 1.906 us 
 *  - For 1 write to DAC
 *  - Measured from one pin toggle (D0) to another 
 */
