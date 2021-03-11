/*
 * Basic ADC input test on the Portenta Board
 *   - 16 bit resolution
 *   - Using a function generator for input to ADC
 *   - Has AREF pin connected to 3.3V
 *
 * Hardware set-up:
 * 1) A0 = analog input to ADC
 * 2) D6 = digital output from ADC
 * 3) Signal generator 
 * 
 * Instructions: 
 *  - Probe ch1 on oscilloscope to A0
 *  - Probe ch2 on oscilloscope to D6
 *  - Dial signal generator from 100 Hz to 2MHz (or the user's preferred frequency range)
 *
 *  Repo Link:
 *  https://github.com/jetzoc/Portenta-Tests.git
 *
 *  March 11, 2021
 */

#include <stdlib.h>

void setup() {
    /* ADC @ 16-bits */
    analogReadResolution(16);

    /* Set up the ADC input pin */
    pinMode(A0, INPUT_PULLDOWN);

    /* Set up a digital pin to probe output */
    pinMode(6, OUTPUT);

    /* Serial terminal baud rate (if needed) */
    Serial.begin(9600);

    Serial.println("*** ADC test on Portenta Board using a Signal Generator ***");

}

void loop() {

  /* Read a value from an analog pin */
  int analog_val = analogRead(A0);

  //UNUSED(analog_val);       // no warnings :)
  //Serial.println(analog_val);

  /* Take the reading and write to a digital pin */
  digitalWrite(6, analog_val);

}

/* RESULTS:
 *  - Cleanest digital conversion signals 
 * are approximately around 1KHz (low-end) to 50-80KHz (high-end)
 */
