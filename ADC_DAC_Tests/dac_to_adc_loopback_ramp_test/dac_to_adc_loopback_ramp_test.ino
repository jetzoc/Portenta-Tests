/*    
 *  DAC to ADC loop test for the Portenta board
 *   - 12 bit resolution for DAC
 *   - 12 bit resolution for ADC
 *   - Uses a software generated signal that outputs the full 12-bit range of DAC
          - Ramp with a step size
 *   - Has AREF pin connected to 3.3V
 *   
 *  Hardware set-up: 
 *  A0 = analog input of ADC 
 *  A6 = analog output from DAC (scope ch. 1)
 *
 *  D6 = digital input connected to analog input of ADC
 *  D7 = digital output of ADC (scope ch. 2)
 *
 *  D0 = digital timing pin for operation
 * 
 *  Connections:
 *  Tie A6 to A0 
 *
 *  For schematic and notes see: https://github.com/jetzoc/Portenta-Tests.git
 *  
 *  March 1, 2021
 */

#include <stdlib.h>

void setup() {
  /* DAC @ 12-bits */
  analogWriteResolution(12);

  /* ADC @ 12-bits */ 
  analogWriteResolution(12); 

  /* Set up the DAC output pin 
   * This pin is probed on oscilloscope */
  pinMode(DAC, OUTPUT);   // pin A6 (analog)

  /* Set up the ADC input pin */ 
  pinMode(A0, INPUT_PULLDOWN);

  /* Set up the ADC output pin (digital) */
  pinMode(6, INPUT);      //  pin D6

  /* Digital wave form from ADC */
  pinMode(7, OUTPUT);     //  pin D7

  /* Set up a digital pin as an output to toggle it (for timing purposes) */
  pinMode(0, OUTPUT);     // pin D0
  
  /* Serial terminal baud rate (if needed) */
  Serial.begin(9600);

  Serial.println("*** DAC to ADC ramp loop test on Portenta Board ***");

}

void loop() {

  /* Toggle digital pin before writing */
  digitalWrite(0, HIGH);
    
  float a_val[4096];
  float d_val[4096];

  /* Write and read back multiple values */
  for (int dac_val = 0; dac_val < 4096; dac_val+=32)   // writes 128x
  {  
    /* Write value to DAC output */
    analogWrite(DAC, dac_val);   // writing to A6
    //Serial.println(dac_val); 
  
    /* Digital read of ADC output */
    d_val[dac_val] = digitalRead(6); 
  }

  /* To view the digital ramp */
  for (int idx = 0; idx < 4096; idx+=32)
  {
    digitalWrite(7, d_val[idx]);
    //Serial.println(d_val[idx]); 
  }

  /* Toggle digital pin after writings */
  digitalWrite(0, LOW);

}

