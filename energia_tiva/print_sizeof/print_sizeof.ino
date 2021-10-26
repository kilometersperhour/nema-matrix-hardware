/*
  DigitalReadSerial with on-board Pushbutton
  Reads a digital input on pin 5, prints the result to the serial monitor 
 
  Harware Required:
  * MSP-EXP430G2 LaunchPad
  
  This example code is in the public domain.
 */

// digital pin 5 has a pushbutton attached to it. Give it a name:
int pushButton = 5;
long myLong; 
word myWord;
short myShort;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial.print("Size of int: ");
  Serial.println(sizeof(buttonState));
  Serial.print("Size of long: ");
  Serial.println(sizeof(myLong));
  Serial.print("Size of word: ");
  Serial.println(sizeof(myWord));
  Serial.print("Size of short: ");
  Serial.println(sizeof(myShort));
  delay(10000);        // delay in between reads for stability
}
