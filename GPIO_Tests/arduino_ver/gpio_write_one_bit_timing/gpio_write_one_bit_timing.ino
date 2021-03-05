/*
 * Sending 1-bit to 1-pin 
 * 
 * Hardware:
 * D15 = output digital pin 
 * D6 = output digital timing pin 
 * 
 * Repo link: https://github.com/jetzoc/Portenta-Tests.git
 * 
 * March 5, 2021 
 */
void setup() {
  
  /* Set up digital pin(s) as output for information */ 
  pinMode(15, OUTPUT);
  
  /* Set up an additional digital pin to toggle for timing purposes */ 
  pinMode(6, OUTPUT); 
}

void loop() {
  
  /* Toggle timing pin */
  digitalWrite(6, HIGH);

  /* Method 1: Write one bit and time it */ 
  //digitalWrite(15, LOW);

  /* Method 2: Write one bit (from a byte) and time it */
  uint8_t test_byte = 0xAA;   // 0b 1010 1010

  digitalWrite(15, bitRead(test_byte, 0));  // sending bit number 0 in test_byte
  
  /* Toggle timing pin */
  digitalWrite(6, LOW);
}

/* Results: 
 *  Method 1: 290 ns for digitalWrite(15, LOW); 
 *  Method 2: 300 ns for digitalWrite(15, bitRead(15, 0));
 */
