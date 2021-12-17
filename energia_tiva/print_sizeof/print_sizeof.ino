// Note from Miles Martin
// The push-button section of the code was irrelevant, and this code was only
// ever functionally intended to provide serial output to indicate the size of 
// variable types that might later be used in the project. 

// For exactitude and clarity of coding, the intXX_t type was ultimately used 
// in other source files because the types are platform-agnostic and are (in 
// many cases) guaranteed to be allocated XX bits.

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
