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
int colSelect = 0;
int rowSelect = 0;

int rowPin[15] = {36, 35, 34, 33, 32, 31, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int colPin[8] = {19, 18, 17, 15, 14, 13, 12, 11};
int rowPinLen = 15;
int colPinLen = 8;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  delay(350);
  Serial.println("Serial connection initialized.");
  inputString.reserve(200);

  // Set all pins in use to low for initialization test
  for (int i = 0; i < rowPinLen; i++) {
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], LOW);
  }
  for (int j = 0; j < colPinLen; j++) {
    pinMode(colPin[j], OUTPUT);
    digitalWrite(colPin[j], LOW);
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
    colSelect = inputString.charAt(0) - '0';
    inputString = inputString.substring(2);

    // now string resembles '1x\n' where x is potentially a number in the ones place
    if (inputString.charAt(1) == '\n') {
      rowSelect = inputString.charAt(0) - '0';
    } else {
      rowSelect = (10*(inputString.charAt(0)-'0') + (inputString.charAt(1)-'0'));
    }
    inputString = inputString.substring(1);

    Serial.print("Setting LED at (");
    Serial.print(colSelect);
    Serial.print(",");
    Serial.print(rowSelect);
    Serial.print(") to state ");
    Serial.print(pinState);
    Serial.println(".");

    // Until pin configurator written, keep the following print statement
    // should prevent confusion about "why it doesn't work"
    //Serial.println("(Nothing has been configured, please write/enable pin configurator)");
    pinConfigurator(pinState,colSelect,rowSelect);
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

void pinConfigurator (int enable, int row, int col) {
  static byte framebuffer[15] = {}; // all possible LEDs, one bit per LED, one byte per row
  static byte prevRow; // possibly useful for efficiency
//  static byte prevCol; // possibly useful for efficiency
  framebuffer[0] = B11111111;
  for (int i = 0; i < 8; i++) { // Disable column
    digitalWrite(colPin[i], LOW);
    //delay(1000); 
  } 
  digitalWrite(prevRow, LOW);                                // Disable row afterward
  digitalWrite(rowPin[row], enable);                         // enable new row
  // row-light-setting loop to enable new col lights. 7-0 grabs MSB and colPin[i] places it at (0,y)
  for (int i = 0; i < 8; i++) { 
    digitalWrite(colPin[i], (framebuffer[row] >> (7-i)) & 0x1);
    //delay(1000);
  }
}

/*
void pinConfigurator2() {
  // test configuration of LED arrays
  for (int i = 0; i < rowPinLen; i++) {
    digitalWrite(rowPin[i], HIGH);
    for (int j = 0; j < colPinLen; j++) {
      digitalWrite(colPin[j], );
      delay(500);
    }
    for (int j = 0; j < colPinLen; j++) {
      digitalWrite(colPin[j], LOW);
    }
    digitalWrite(rowPin[i], LOW);
    delay(2500);
  }

  // Set all pins in use to low so they don't float or anything
  for (int i = 0; i < rowPinLen; i++) {
    digitalWrite(rowPin[i], LOW);
  }
  for (int j = 0; j < colPinLen; j++) {
    digitalWrite(colPin[j], LOW);
  }
  
}
*/

/*void pinConfigurator (int enable, int row, int col) {
  static byte framebuffer[15] = {}; // all possible LEDs, one bit per LED, one byte per row
  static byte prevRow; // possibly useful for efficiency
//  static byte prevCol; // possibly useful for efficiency
  framebuffer = 
  for (int i = 0; i < 8; i++) { // Disable column
    digitalWrite(colPin[i], LOW); 
  } 
  digitalWrite(prevRow, LOW);                                // Disable row afterward
  digitalWrite(rowPin[row], enable);                         // enable new row
  // row-light-setting loop to enable new col lights. 7-0 grabs MSB and colPin[i] places it at (0,y)
  for (int i = 0; i < 8; i++) { 
    digitalWrite(colPin[i], (framebuffer[row] >> (7-i)) & 0x1);
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
