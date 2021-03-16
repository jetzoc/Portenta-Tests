/*
 * Basic ADC -> DAC test on the Portenta Board
 *   - 12 bit resolution
 *   - Using a function generator for input to ADC
 *   - Has AREF pin connected to 3.3V
 *
 * Hardware set-up:
 * 1) A0 = analog input to ADC
 * 2) A6 = analog output of DAC
 * 3) Signal generator
 *    - Freq: 1KHz
 *    - Ampl: 3.3V
 *    - Offset: 1.65V
 *    - Duty: 50%
 *    - Phase: 0.0
 * 
 * Instructions: 
 *  - Probe ch1 on oscilloscope to A0
 *  - Probe ch2 on oscilloscope to A6
 *
 *  Repo Link:
 *  https://github.com/jetzoc/Portenta-Tests.git
 *
 *  March 11, 2021
 */

#include <stdlib.h>
#define ADC_IN A0 
#define NUM_OF_SAMPLES 2000
#define ADC_DAC_RESOLUTION 12
/* Read several values from ADC input */
int analog_vals[NUM_OF_SAMPLES]; 
 
void setup() {
    /* Set ADC resolution */
    analogReadResolution(ADC_DAC_RESOLUTION);

    /* Set DAC resolution */ 
    analogWriteResolution(ADC_DAC_RESOLUTION); 

    /* Set up the ADC input pin */
    pinMode(ADC_IN, INPUT_PULLDOWN);

    /* Set up the DAC output pin */
    pinMode(DAC, OUTPUT);

    /* Serial terminal baud rate (if needed) */
    Serial.begin(9600);

    Serial.println("*** ADC test on Portenta Board using a Signal Generator ***");

}

void loop() {

  const int high_lvl = pow(2,ADC_DAC_RESOLUTION) - 1; 
  const int low_lvl = 0; 
  //Serial.println("MOST HIGH: " + String(high_lvl));

  if (analogRead(ADC_IN) == high_lvl)
  {
    for (int i = 0; i < NUM_OF_SAMPLES; i++) 
    {
      analog_vals[i] = analogRead(ADC_IN);  // 5 us operation 
      //delay(5);  //  5 us
    }

    /* Uncomment to see the samples in the Serial Monitor */ 
    // for (int i = 0; i < NUM_OF_SAMPLES; i++)
    // {
    //   Serial.println(analog_vals[i]);
    // }

    // Serial.println("----------");
    
    while(1) 
    {
      /* Write samples to DAC */
      for (int i = 0; i < NUM_OF_SAMPLES; i++)
      {
        analogWrite( DAC, analog_vals[i] ); // 2 us operation
        //delay(1); 
      }
      // for (int i = NUM_OF_SAMPLES/2; i < NUM_OF_SAMPLES; i++)
      // {
      //   analogWrite( DAC, analog_vals[i]);
      // }
    }
  }
}

/* RESULTS:
 *
 */
