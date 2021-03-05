/*
 * Blinky program for LEDs 
 * using the Arduino language on the Portenta H7 board
 *
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 * 
 * February 24, 2021
*/
#include <stdlib.h>

void setup() {
  
  /* Initialzing LEDs */
  pinMode(LED_BUILTIN, OUTPUT);    // green LED
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);

}

void loop() {

  int wait_tm = 500; 
  
  // /* Blink green LED */ 
  // digitalWrite(LED_BUILTIN, LOW);   
  // delay(wait_tm);                       
  // digitalWrite(LED_BUILTIN, HIGH);    
  // delay(wait_tm);

  // /* Blink red LED */ 
  // digitalWrite(LEDR, LOW);         
  // delay(wait_tm);                     
  // digitalWrite(LEDR, HIGH);          
  // delay(wait_tm);

  /* Blink blue LED */ 
  digitalWrite(LEDB, LOW);         
  delay(wait_tm);                      
  digitalWrite(LEDB, HIGH);          
  delay(wait_tm);
  
}
