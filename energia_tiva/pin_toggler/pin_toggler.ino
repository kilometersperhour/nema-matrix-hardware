/*
  Based on "Serial Event"

  Created 9 May 2011
  by Tom Igoe
  Modified 24 April 2013
  by Sean Alvarado
  Modified October 2021
  by Miles Martin

  When new serial data arrives, the original sketch added it to a String.
  This behavior was adapted to read in more purposeful information and extract an 
  ordered pair from it. The ordered pair would be used to determine the 
  "coordinates" of the pixel to light. A pixel located in row y within column x
  would be activated with "on x y" or "on x yy". The code can handle both formats
  because at the time of writing, the hardware requirements necessitated access 
  to 8 columns and 15 rows. 
  
  This "lineage" of code was most useful when testing connectivity issues 
  between the matrix displays and the microcontroller, as the breadboarded jumpers could
  sometimes come loose. Later, the hardware was upgraded to thicker-gauge jumpers that 
  limited the occurrence of these issues.

  The example code sampled is in the public domain and is included with the Energia 
  IDE which programs the Tiva C Launchpad board used in the capstone product presented
  during the mid-December 2021 design review. This is a checkpoint int the pin_toggler 
  source history at which point a "backup" counterpart was created and the changes 
  made in the backup file ended up being more desirable than the original source.
  Changes were made to the copy with "backup" appended because the Energia IDE is 
  particular about the names and folder structure of source files, so it was best to 
  modify the duplicate (i.e. the backup).

*/

/* Things to do:
 * Error checking
 */

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;
int colSelect = 0;
int rowSelect = 0;

int rowPin[22] = {28, 27, 26, 25, 24, 23, 8, 5, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 11, 12, 13, 17};
//int colPin[4] = {14, 15, 18, 19};
int colPin[4] = {14, 15, 2, 19};
int rowPinLen = 22;
int colPinLen = 4;
char outputString[100];

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
    sprintf(outputString,"Setting LED at (%d,%d) to state %d.\n",colSelect,rowSelect,pinState);
/*    Serial.print("Setting LED at (");
    Serial.print(colSelect);
    Serial.print(",");
    Serial.print(rowSelect);
    Serial.print(") to state ");
    Serial.print(pinState);
    Serial.println(".");
*/  
    Serial.println(outputString);
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

void pinConfigurator (int enable, int col, int row) {
//  static byte framebuffer[15] = {}; // all possible LEDs, one bit per LED, one byte per row
//  static byte prevRow; // possibly useful for efficiency
//  static byte prevCol; // possibly useful for efficiency
  Serial.println("ATTN: AUTO-OFF ENABLED");
  for (int i = 0; i < colPinLen; i++) { // Disable column
    digitalWrite(colPin[i], LOW);
    //delay(1000); 
  }
  for (int i = 0; i < rowPinLen; i++) { // Disable column
    digitalWrite(rowPin[i], LOW);
    //delay(1000); 
  } 
  sprintf(outputString,"Running digitalWrite(%d, %d) given row = %d",rowPin[row],enable,row);
  Serial.println(outputString);
  digitalWrite(rowPin[row], enable);                         // enable new row
  sprintf(outputString,"Running digitalWrite(%d, %d) given col = %d",colPin[col],enable,col);
  Serial.println(outputString);
  digitalWrite(colPin[col], enable);                           // enable new col

  // row-light-setting loop to enable new col lights. 7-0 grabs MSB and colPin[i] places it at (0,y)
/*  for (int i = 0; i < rowPinLen; i++) { 
    digitalWrite(colPin[i], (framebuffer[row] >> (7-i)) & 0x1);
    //delay(1000);
  }
*/}

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
