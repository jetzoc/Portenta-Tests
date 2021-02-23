/*    
 *  DAC signal conversion test for the Portenta board 
 *   - 12 bit resolution
 *   - Uses an external square waveform set at 1 KHz
 *        - Obtained from scope test signal
 *   - Has AREF pin connected to 3.3V
 *   
 *  Hardware set-up: 
 *  A6 = analog output from DAC (scope ch. 2)
 *  D0 = digital output for timing purposes 
 *  D1 = digital input for Analog signal coming from the DAC (scope ch. 1)
 * 
 *  For schematic and notes see: https://github.com/jetzoc/Portenta_Tests.git
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

  /* Set up another digital pin to see the conversion back to digital (from the analog DAC pin) */
  pinMode(1, INPUT_PULLDOWN);
  
  /* Serial terminal baud rate (if needed) */
  Serial.begin(9600);

  Serial.println("*** DAC test on Portenta Board: External input square waveform version ***");

}

void loop() {

  /* Toggle a digital pin before reading */
  digitalWrite(0, HIGH);

  /* Read the input digital waveform from D1 */
  int dig_in = digitalRead(1); 

  /* Write the digital input received from the DAC output */ 
  analogWrite(DAC, dig_in); 
    
  /* Toggle digital pin again */
  digitalWrite(0, LOW);

}
