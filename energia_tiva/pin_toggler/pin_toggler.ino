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

/*
 * 
 */

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;
int colSelect = 0;
int rowSelect = 0;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString); 
    // toggle appropriate pin
    //if (!(inputString.startsWith("on ") || inputString.startsWith("off "))) {
    //  Serial.println("Malformed command! Try again with 'on 0 1' to turn on LED at position (0,1), for example")
    //} else {
    //  while (inputString != "") {
    //    lastCommand = inputString.lastIndexOf(' ');
    //  }
    
    Serial.print("inputString before determining on/off = '");
    Serial.print(inputString);
    Serial.print("'");
    Serial.println();    
    if (inputString.startsWith("of")) {
      pinState = 0;
    } else if (inputString.startsWith("on")) {
      pinState = 1;
    }
    // delete [of ] or [on ]
    inputString = inputString.substring(3); 
    
    // now string resembles '0 1x\n' where x is potentially a number in the ones place
    Serial.print("inputString before determining column = '");
    Serial.print(inputString);
    Serial.print("'");
    Serial.println();    
    colSelect = inputString.charAt(0) - '0';
    inputString = inputString.substring(2);

    // now string resembles '1x\n' where x is potentially a number in the ones place
    Serial.print("inputString before determining row = '");
    Serial.print(inputString);
    Serial.print("'");
    Serial.println();    
    if (inputString.charAt(1) == '\n') {
      rowSelect = inputString.charAt(0) - '0';
    } else {
      rowSelect = (10*(inputString.charAt(0)-'0') + (inputString.charAt(1)-'0'));
    }
    inputString = inputString.substring(1);
    
    Serial.print("inputString at end of iteration = '");
    Serial.print(inputString);
    Serial.print("'");
    Serial.println();

    Serial.print("Setting LED at (");
    Serial.print(colSelect);
    Serial.print(",");
    Serial.print(rowSelect);
    Serial.print(") to state ");
    Serial.print(pinState);
    Serial.println(".");

    // Until pin configurator written, keep the following print statement
    // should prevent confusion about "why it doesn't work"
    Serial.println("(Nothing has been configured, please write/enable pin configurator)");
    //    Serial.println("Pin reconfigured.");

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

void pinConfigurator () {
  
}

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
