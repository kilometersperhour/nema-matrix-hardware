/*
  Based on "Serial Event example"

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and 
  clears it.

  A good test for this is to try it with a GPS receiver 
  that sends out NMEA 0183 sentences. 

  Created 9 May 2011
  by Tom Igoe
  Modified 24 April 2013
  by Sean Alvarado

  Hardware Required:
  * MSP-EXP430G2 LaunchPad
  
  This example code is in the public domain.

*/

/* Things to do:
 * Error checking
 */

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;
int matrixSelect = 0;
int pixelSelect = 0;
/* 
pixelPin and matrixPin map to the pins controlling the gates for the per-pixel and per-display power
*/
//int pixelPin[22] = {28, 29, 26, 25, 24, 23, 8, 5, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 11, 12, 13, 17};
//int matrixPin[4] = {14, 15, 18, 19};
int pixelPin[22] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 3, 4, 40, 11, 12, 13, 17};
int matrixPin[4] = {14, 15, 18, 19};
int pixelPinLen = 22;
int matrixPinLen = 4;
char outputString[100];

void setup() {
  // initialize serial:
  Serial.begin(9600);
  delay(500);
  Serial.println("Serial connection initialized.");
  inputString.reserve(200);

  // Set all pins in use to low for initialization test
  for (int i = 0; i < pixelPinLen; i++) {
    pinMode(pixelPin[i], OUTPUT);
    digitalWrite(pixelPin[i], LOW);
  }
  for (int j = 0; j < matrixPinLen; j++) {
    pinMode(matrixPin[j], OUTPUT);
    digitalWrite(matrixPin[j], LOW);
  }
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString); 

    if (inputString.startsWith("of")) {
      pinState = 0;
    } else if (inputString.startsWith("on")) {
      pinState = 1;
    }
    // delete [of ] or [on ]
    inputString = inputString.substring(3); 
    
    // now string resembles '0 1x\n' where x is potentially a number in the ones place
    matrixSelect = inputString.charAt(0) - '0';
    inputString = inputString.substring(2);

    // now string resembles '1x\n' where x is potentially a number in the ones place
    if (inputString.charAt(1) == '\n') {
      pixelSelect = inputString.charAt(0) - '0';
    } else {
      pixelSelect = (10*(inputString.charAt(0)-'0') + (inputString.charAt(1)-'0'));
    }
    inputString = inputString.substring(1);
    sprintf(outputString,"Setting LED at (%d,%d) to state %d.\n",matrixSelect,pixelSelect,pinState);
/*    Serial.print("Setting LED at (");
    Serial.print(matrixSelect);
    Serial.print(",");
    Serial.print(pixelSelect);
    Serial.print(") to state ");
    Serial.print(pinState);
    Serial.println(".");
*/  
    Serial.println(outputString);
    // Until pin configurator written, keep the following print statement
    // should prevent confusion about "why it doesn't work"
    //Serial.println("(Nothing has been configured, please write/enable pin configurator)");
    pinConfigurator(pinState,matrixSelect,pixelSelect);
    Serial.println("Pin reconfigured.");

    Serial.println();
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX. This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
    stringComplete = true;
    } 
  }
}

void pinConfigurator (int enable, int matrix, int pixel) {
//  static byte framebuffer[15] = {}; // all possible LEDs, one bit per LED, one byte per pixel
//  static byte prevPixel; // possibly useful for efficiency
//  static byte prevMatrix; // possibly useful for efficiency
  Serial.println("ATTN: AUTO-OFF ENABLED");
  for (int i = 0; i < matrixPinLen; i++) { // Disable matrix
    digitalWrite(matrixPin[i], LOW);
    //delay(1000); 
  }
  for (int i = 0; i < pixelPinLen; i++) { // Disable pixels per matrix
    digitalWrite(pixelPin[i], LOW);
    //delay(1000); 
  } 
  sprintf(outputString,"Running digitalWrite(%d, %d) given pixel = %d",pixelPin[pixel],enable,pixel);
  Serial.println(outputString);
  digitalWrite(pixelPin[pixel], enable);                         // enable new pixel
  sprintf(outputString,"Running digitalWrite(%d, %d) given matrix = %d",matrixPin[matrix],enable,matrix);
  Serial.println(outputString);
  digitalWrite(matrixPin[matrix], enable);                           // enable new matrix

  // pixel-light-setting loop to enable new matrix lights. 7-0 grabs MSB and matrixPin[i] places it at (0,y)
/*  for (int i = 0; i < pixelPinLen; i++) { 
    digitalWrite(matrixPin[i], (framebuffer[pixel] >> (7-i)) & 0x1);
    //delay(1000);
  }
*/}

/*
void pinConfigurator2() {
  // test configuration of LED arrays
  for (int i = 0; i < pixelPinLen; i++) {
    digitalWrite(pixelPin[i], HIGH);
    for (int j = 0; j < matrixPinLen; j++) {
      digitalWrite(matrixPin[j], );
      delay(500);
    }
    for (int j = 0; j < matrixPinLen; j++) {
      digitalWrite(matrixPin[j], LOW);
    }
    digitalWrite(pixelPin[i], LOW);
    delay(2500);
  }

  // Set all pins in use to low so they don't float or anything
  for (int i = 0; i < pixelPinLen; i++) {
    digitalWrite(pixelPin[i], LOW);
  }
  for (int j = 0; j < matrixPinLen; j++) {
    digitalWrite(matrixPin[j], LOW);
  }
  
}
*/

/*void pinConfigurator (int enable, int pixel, int matrix) {
  static byte framebuffer[15] = {}; // all possible LEDs, one bit per LED, one byte per pixel
  static byte prevPixel; // possibly useful for efficiency
//  static byte prevMatrix; // possibly useful for efficiency
  framebuffer = 
  for (int i = 0; i < 8; i++) { // Disable matrix
    digitalWrite(matrixPin[i], LOW); 
  } 
  digitalWrite(prevpixel, LOW);                                // Disable pixel afterward
  digitalWrite(pixelPin[pixel], enable);                         // enable new pixel
  // pixel-light-setting loop to enable new matrix lights. 7-0 grabs MSB and matrixPin[i] places it at (0,y)
  for (int i = 0; i < 8; i++) { 
    digitalWrite(matrixPin[i], (framebuffer[pixel] >> (7-i)) & 0x1);
  }
}*/

// Error checking for later!! Get the functionality going first
/*boolean containsSpaces(String buffer) {
  char searchChar = ' ';
  boolean stringContainsSpaces = true;
  int startIndex = 0;
  while (stringContainsSpaces == true) {
    if ((startIndex = buffer.indexOf(searchChar, startIndex)) > 0) { // if searchChar is found
    } else {
      stringContainsSpace = false;
    }
  }
}*/
