/*
   To-dos:
      Create framebuffer manager
      Error checking
      Move away from globals
      Change variables to smaller types
      Add better comments
      Make functions
*/
#include "helper_functions.h"

#ifndef MATRICES_PER_DISPLAY
#include "ff_scoreboard_properties.h"
#endif



String inputString = ""; // a string to hold incoming data
char outputString[100];
boolean stringComplete = false; // whether the string is complete

extern const int pixelPin[];
extern const int matrixPin[];

extern int matrixValue[]; // set time by reading serial
// TODO set to {10, 10, 10, 10} for final, so matrix is blank on failed initial read

extern const int numberIndexInString[]; // determines location of time digits within input string
extern const uint32_t glyphs[];

/*
void setMuxingPinsLow();
void setMatrixValue(int *, int);
boolean inputStringValid(String);
boolean timeStringValid(String);
*/

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  if (DEBUG) { Serial.println("Serial connection initialized."); } 
  
  // Set all pins in use to low for initialization test
  setMuxingPinsLow();

}

void loop() {
  // put your main code here, to run repeatedly:

  if (stringComplete) {
    
    if (DEBUG) {
      if (VERBOSE) { Serial.println("Reached top of loop"); }
      Serial.println(inputString);
    }

    stringComplete = (inputStringValid(inputString) && timeStringValid(inputString));
    // now string resembles '+[0-:][0-:]:[0-:][0-:]\n' 
    if (stringComplete == true) {
      setMatrixValue(&matrixValue[0], inputString, 1);
      setMatrixValue(&matrixValue[1], inputString, 2);
      setMatrixValue(&matrixValue[2], inputString, 4);
      setMatrixValue(&matrixValue[3], inputString, 5);
    }

    if (DEBUG) {
      sprintf(outputString, "Setting matrices to show %d%d:%d%d given ", matrixValue[0], matrixValue[1], matrixValue[2], matrixValue[3]);
      Serial.println((outputString+inputString));
      Serial.println();
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  drawDigitalDisplay(matrixValue);
}
  /*

  */

  /*
  for (int matrix = 0; matrix < MATRICES_PER_DISPLAY; matrix++) { // per-matrix drawing loop
    digitalWrite(matrixPin[matrix], HIGH); // disable the current matrix, comment out to watch pixels blink out
    for (int pixel = 0; pixel < PIXELS_PER_MATRIX; pixel++) { // per-pixel deactivation loop
      digitalWrite(pixelPin[pixel], LOW); // Disable pixel by pixel, clean slate
    }
    for (int i = 0; i < 10; i++) {
      delayMicroseconds(REFRESH_WAIT);
      for (int pixel = 0; pixel < PIXELS_PER_MATRIX; pixel++) { // per-pixel drawing loop
        // This is a pixel-light-setting loop to enable new matrix lights.
        if (matrix == 0) { // if 'plexing tens of hours
          digitalWrite(pixelPin[pixel], ((glyphs[matrixValue[0]] >> pixel) & 0x1));
        }
        if (matrix == 1) { // if 'plexing ones of hours
          digitalWrite(pixelPin[pixel], ((glyphs[matrixValue[1]] >> pixel) & 0x1));
        }
        if (matrix == 2) { // if 'plexing tens of minutes
          digitalWrite(pixelPin[pixel], ((glyphs[matrixValue[2]] >> pixel) & 0x1));
        }
        if (matrix == 3) { // if 'plexing ones of minutes
          digitalWrite(pixelPin[pixel], ((glyphs[matrixValue[3]] >> pixel) & 0x1));
        }
        if (DEBUG && VERBOSE) {
          Serial.print("pixel ");
          Serial.print(pixel);
          Serial.print(" matrix ");
          Serial.print(matrix);
          Serial.print(" numeral ");
          Serial.println(i);
        }
      }
    }
    digitalWrite(matrixPin[matrix], LOW); // disable the current matrix, comment out to watch pixels blink out
    
    if (DEBUG && VERBOSE) {
      Serial.print("Pin ");
      Serial.print(matrix);
      Serial.println(" reconfigured.");
    }
  }
}
*/
/*
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

void setMuxingPinsLow() {

  for (int i = 0; i < PIXELS_PER_MATRIX; i++) {
    pinMode(pixelPin[i], OUTPUT);
    digitalWrite(pixelPin[i], LOW);
  }
  for (int j = 0; j < MATRICES_PER_DISPLAY; j++) {
    pinMode(matrixPin[j], OUTPUT);
    digitalWrite(matrixPin[j], LOW);
  }
  
}
// check that the format (+WX:YZ) is present, where W, X, Y, and Z are any value
boolean inputStringValid(String theInput) {

  boolean isValid = false;

  if (theInput.startsWith("+")) {
    if (theInput.charAt(3) == ':') {
      isValid = true;
    }
  } else {
    isValid = false;
  }

  return isValid;
}

// check that the values W, X, Y, and Z of string "+WX:YZ" contains valid indices within glyphs[]
// where W, X, Y, and Z are expected to be any value between 0 and (GLYPHS_COUNT-1) inclusive
// if invalid value anywhere, return false
boolean timeStringValid(String theInput) {

  int indexToTest = -1; // an invalid index to start; should be assigned in loop
  boolean isValid = true; // assume valid until proved invalid

  for (int pos = numberIndexInString[0]; pos < numberIndexInString[(MATRICES_PER_DISPLAY-1)]; pos++) { // only checks positions 1, 2, 4, 5
        
    indexToTest = theInput.charAt(pos) - '0';
        
    if (pos == 3) { 
      pos++; 
    }
        
    // test: is array index not gt/eq 0, and not lt/eq array length 
    //                                  (array length is invalid index, must be less) 
    if (!(0 <= indexToTest) && !(indexToTest <= GLYPHS_COUNT)) { 
      isValid = false;
      return false; 
    }
  }
  if (isValid == true) { // safeguard case that isValid == false but somehow execution has reached here 
    return true; 
  }
}
*/
void setMatrixValue(int *matrixIndex, int pos) {
  int value = (inputString.charAt(pos) - '0');
  if ((0 <= value)  && (value < GLYPHS_COUNT)) {
    *matrixIndex = value;
  } 
  else {  // error character: GLYPH_ALL_ON (so, 11). should not be possible if timeStringValid(inputString) == true
    *matrixIndex = 11;
  }

  if (DEBUG) {
    Serial.print(value);
    Serial.print(" ");
    Serial.println(pos);
  }
}
