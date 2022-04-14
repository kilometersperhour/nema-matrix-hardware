/*
   To-dos:
      Create framebuffer manager
      Error checking
      Move away from globals
      Change variables to smaller types
      Add better comments
      Make functions
*/
// Number of glyphs encoded for display on any given matrix
#define GLYPHS_COUNT 12
// number of microseconds to wait before refreshing all matrices
#define REFRESH_WAIT 400 // microseconds
// Enable serial/UART print statements
#define DEBUG false
#define VERBOSE false

const int pixelPinLen = 22;
const int matrixPinLen = 4;
const int pixelPin[pixelPinLen] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 39, 38, 40, 11, 12, 13, 17};
const int matrixPin[matrixPinLen] = {14, 15, 18, 19};

String inputString = "+12:00"; // a string to hold incoming data
char outputString[100];
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;

int matrixGlyphs[matrixPinLen] = {0, 0, 0, 0}; // set time by reading serial

void setMuxingPinsLow();

void parseTimeString();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  // Set all pins in use to low for initialization test
  setMuxingPinsLow();

}

int waittime = 4; // 4ms = <62.5Hz/display, 25% duty cycle

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
const uint32_t zero = (B00000000 << 24) + (B00010011 << 16) + (B01100100 << 8) + B11010110;
const uint32_t one = (B00000000 << 24) + (B00010100 << 16) + (B00010010 << 8) + B00100100;
const uint32_t two = (B00000000 << 24) + (B00111010 << 16) + (B10010000 << 8) + B01010110;
const uint32_t three = (B00000000 << 24) + (B00010011 << 16) + (B00010000 << 8) + B01010110;
const uint32_t four = (B00000000 << 24) + (B00100001 << 16) + (B11100101 << 8) + B01101000;
const uint32_t five = (B00000000 << 24) + (B00010011 << 16) + (B00100011 << 8) + B10011111;
const uint32_t six = (B00000000 << 24) + (B00010011 << 16) + (B01011100 << 8) + B10010110;
const uint32_t seven = (B00000000 << 24) + (B00001010 << 16) + (B10010000 << 8) + B01001111;
const uint32_t eight = (B00000000 << 24) + (B00010011 << 16) + (B01011000 << 8) + B11010110;
const uint32_t nine = (B00000000 << 24) + (B00010001 << 16) + (B00111000 << 8) + B11010110;
const uint32_t allOff = (B00000000 << 24) + (B00000000 << 16) + (B00000000 << 8) + B00000000;
const uint32_t allOn = (B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111;
// if adding/removing glyphs, be sure to update GLYPHS_COUNT

// maybe change to "glyphs" with indices 10+ as blank, all pixels, etc.
const uint32_t numberGlyphs[GLYPHS_COUNT] = {zero, one, two, three, four, five, six, seven, eight, nine, allOff, allOn};

void loop() {
  // put your main code here, to run repeatedly:

  if (true || stringComplete) {
    
    if (DEBUG) {
      if (VERBOSE) {
        Serial.println("top"); // todo remove
      }
      Serial.println(inputString); // 
    }
    
    if (inputString == "") {
      stringComplete = false;
    } else if (inputString.startsWith("+")) { // TODO make a validity tester function
      stringComplete = true;

      for (int x = 0; x < matrixPinLen; x++) { 
        matrixGlyphs[x] = 0;
      }
    } else {
      stringComplete = false;
    }
    // now string resembles '+[01][0-9]:[0-9][0-9]\n' 
    if (inputString.charAt(3) == ':') {
      matrixGlyphs[0] = (inputString.charAt(1) - '0');
      matrixGlyphs[1] = (inputString.charAt(2) - '0');
      matrixGlyphs[2] = (inputString.charAt(4) - '0');
      matrixGlyphs[3] = (inputString.charAt(5) - '0');
    }
    if (DEBUG) {
      sprintf(outputString, "Setting matrices to show %d%d:%d%d given ", matrixGlyphs[0], matrixGlyphs[1], matrixGlyphs[2], matrixGlyphs[3]);
      Serial.println((outputString+inputString));
      Serial.println();
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  for (int matrix = 0; matrix < matrixPinLen; matrix++) { // per-matrix drawing loop
    digitalWrite(matrixPin[matrix], HIGH); // disable the current matrix, comment out to watch pixels blink out
    for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel deactivation loop
      digitalWrite(pixelPin[pixel], LOW); // Disable pixel by pixel, clean slate
    }
    for (int i = 0; i < 10; i++) {
      delayMicroseconds(REFRESH_WAIT);//delay(1); //100us
      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel drawing loop
        // This is a pixel-light-setting loop to enable new matrix lights.
        // (7-0) grabs MSB and matrixPin[i] places it at (0,y), for example
        //          digitalWrite(pixelPin[pixel], (matrixFramebuffer[matrix] >> pixel) & 0x1);
        if (matrix == 0) { // if 'plexing tens of hours
          digitalWrite(pixelPin[pixel], ((numberGlyphs[matrixGlyphs[0]] >> pixel) & 0x1));
        }
        if (matrix == 1) { // if 'plexing ones of hours
          digitalWrite(pixelPin[pixel], ((numberGlyphs[matrixGlyphs[1]] >> pixel) & 0x1));
        }
        if (matrix == 2) { // if 'plexing tens of minutes
          digitalWrite(pixelPin[pixel], ((numberGlyphs[matrixGlyphs[2]] >> pixel) & 0x1));
        }
        if (matrix == 3) { // if 'plexing ones of minutes
          digitalWrite(pixelPin[pixel], ((numberGlyphs[matrixGlyphs[3]] >> pixel) & 0x1));
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
      //delayMicroseconds(waittime*100);
    }      
    digitalWrite(matrixPin[matrix], LOW); // disable the current matrix, comment out to watch pixels blink out
    
    if (DEBUG && VERBOSE) {
      Serial.print("Pin ");
      Serial.print(matrix);
      Serial.println(" reconfigured.");
    }
  }
}

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

  for (int i = 0; i < pixelPinLen; i++) {
    pinMode(pixelPin[i], OUTPUT);
    digitalWrite(pixelPin[i], LOW);
  }
  for (int j = 0; j < matrixPinLen; j++) {
    pinMode(matrixPin[j], OUTPUT);
    digitalWrite(matrixPin[j], LOW);
  }
  
}
