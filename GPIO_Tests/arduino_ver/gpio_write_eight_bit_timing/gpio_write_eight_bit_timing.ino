/*
 * Sending 1-bit to 8 different pins 
 * 
 * Hardware:
 * D15-21 and D0 = output digital pins
 * D6 = output digital timing pin 
 * 
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 * 
 * March 4, 2021
 */

void setup() {
  
  /* Set up eight digital pins as output for information */ 
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(0, OUTPUT);

  /* Set up an additional digital pin to toggle for timing purposes */ 
  pinMode(6, OUTPUT); 
}

void loop() {
  
  while(1) 
  {
    uint8_t test_byte = 0xAA; 

    /* Toggle timing pin */
    digitalWrite(6, HIGH);

    /* Write one bit to eight different pins */
    digitalWrite(15, bitRead(test_byte, 0));
    digitalWrite(16, bitRead(test_byte, 1));
    digitalWrite(17, bitRead(test_byte, 2));
    digitalWrite(18, bitRead(test_byte, 3));
    
    digitalWrite(19, bitRead(test_byte, 4));
    digitalWrite(20, bitRead(test_byte, 5)); 
    digitalWrite(21, bitRead(test_byte, 6));
    digitalWrite(0, bitRead(test_byte, 7)); 
      
    /* Toggle timing pin */
    digitalWrite(6, LOW);
  }
}

/*
 * Results: 
 * 1.32us for all eight operations
 */
