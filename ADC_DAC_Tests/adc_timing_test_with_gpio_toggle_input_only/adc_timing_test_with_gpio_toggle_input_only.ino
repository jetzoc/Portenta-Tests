/*
 * Basic ADC input test on the Portenta Board
 *   - 16 bit resolution
 *   - Uses a 10K Potentiometer hooked up to 3.3V
 *   - Has AREF pin connected to 3.3V
 *   
 *  Hardware set-up: 
 *  A0 = analog input to ADC
 *  D0 = digital output for timing purposes (scope ch. 1)
 *  D6 = digital input connected to analog input of ADC
 *  D7 = digital output of ADC (scope ch. 2)
 *  
 *  Don't forget to turn the dial on the POT to see results!!
 *     - Analog number moves from 0 to 65535
 *  
 *  For schematic and notes see: https://github.com/jetzoc/Portenta-Tests.git
 *  
 *  February 22, 2021
 */
 
#include <stdlib.h>

void setup() {
    /* ADC @ 16-bits */
    analogReadResolution(16);

    /* Set up the ADC input pin */ 
    pinMode(A0, INPUT_PULLDOWN);

    /* Set up a digital pin as an output to toggle it */
    pinMode(0, OUTPUT);    // pin D0

    /* Serial terminal baud rate (if needed) */
    Serial.begin(9600);

    Serial.println("*** ADC test on Portenta Board ***");
    
}

void loop() {

  /* Toggle a digital pin before reading */
  digitalWrite(0, HIGH);    
  
  /* Read a value from an analog pin */ 
  int analog_val = analogRead(A0);
  UNUSED(analog_val);       // no warnings :)
  //Serial.println(analog_val);  

  /* Toggle digital pin again */
  digitalWrite(0, LOW); 
  
}

/* RESULTS: 
 *  deltaT = 4.88 us
 *  - For one ADC input read
 *  - Measured from one pin toggle (D0) to another 
 */
