/*
   To-dos:
      Create framebuffer manager
      Error checking
      Move away from globals
      Change variables to smaller types
      Add better comments
      Make functions
*/

int matrixSelect = 0;
int pixelSelect = 17;
const int pixelPin[22] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 39, 38, 40, 11, 12, 13, 17};
const int matrixPin[4] = {14, 15, 18, 19};
const int pixelPinLen = sizeof(pixelPin[])/sizeof(pixelPin[0]); //22;
const int matrixPinLen = sizeof(matrixPin[])/sizeof(matrixPin[0]); //4;

String inputString = ""; // a string to hold incoming data
char outputString[100];
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;

int debug = 0;

void setMuxingPinsLow();

void parseTimeString();

void writeNumeralsAll(int h10, int h01, int m10, int m01);

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

uint32_t numberGlyphs[10] = {zero, one, two, three, four, five, six, seven, eight, nine};



void loop() {
  // put your main code here, to run repeatedly:


//For testing purposes only, for use in debug writers
const uint32_t debugMatrixFramebufferMask[4] = {(B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111}; //
const uint32_t debugMatrixFramebuffer[4] =  {((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                        ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                        ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                        ((B00000000 << 24) + (B00100001 << 16) + (B00100000 << 8) + B01001000), // one
                                 };
*/

  while (1) { // big loop
    if (stringComplete) {
      Serial.println(inputString); // 

      if (inputString.startsWith("+") || inputString.startsWith("-")) {
        stringComplete = false;
      } else {
        stringComplete = true;
      }
      // delete [+] or [-] at beginning of string
      inputString = inputString.substring(3);

      // now string resembles 'xx:yy\n' where x is potentially a number in the ones place
      if (inputString.charAt(2) == ':') {
        pixelSelect = (10 * (inputString.charAt(0) - '0') + (inputString.charAt(1) - '0'));
      }
      inputString = inputString.substring(3);

      // now string resembles '1x\n' where x is potentially a number in the ones place
      if (inputString.charAt(1) == '\n') {
        pixelSelect = inputString.charAt(0) - '0';
      } else {
        pixelSelect = (10 * (inputString.charAt(0) - '0') + (inputString.charAt(1) - '0'));
      }
      inputString = inputString.substring(2);
      if (debug) {
        sprintf(outputString, "Setting LED at (%d,%d) to state %d.\n", matrixSelect, pixelSelect, pinState);
        Serial.println(outputString);
      }

      Serial.println();
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
/*    for (int matrix = 0; matrix < matrixPinLen; matrix++) { // per-matrix drawing loop
      digitalWrite(matrixPin[matrix], HIGH); // disable the current matrix, comment out to watch pixels blink out

      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel deactivation loop
        digitalWrite(pixelPin[pixel], LOW); // Disable pixel by pixel, clean slate
      }
      // make function: void writeNumeralsAll(int select, int h10, int h01, int m10, int m01); 
      for (int i = 0; i < 10; i++) {
        delayMicroseconds(waittime*100);//delay(1);
        for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel drawing loop
          // This is a pixel-light-setting loop to enable new matrix lights.
          // (7-0) grabs MSB and matrixPin[i] places it at (0,y), for example
          //          digitalWrite(pixelPin[pixel], (matrixFramebuffer[matrix] >> pixel) & 0x1);
          if (matrix == 0) {
            digitalWrite(pixelPin[pixel], ((numberGlyphs[1] >> pixel) & 0x1));
          }
          if (matrix == 1) {
            digitalWrite(pixelPin[pixel], ((numberGlyphs[3] >> pixel) & 0x1));
          }
          if (matrix == 2) {
            digitalWrite(pixelPin[pixel], ((numberGlyphs[3] >> pixel) & 0x1));
          }
          if (matrix == 3) {
            digitalWrite(pixelPin[pixel], ((numberGlyphs[7] >> pixel) & 0x1));
          }
          if (debug > 1) {
            Serial.print("pixel ");
            Serial.print(pixel);
            Serial.print(" matrix ");
            Serial.print(matrix);
            Serial.print(" state ");
            Serial.print((numberGlyphs[pixelSelect % 10] >> pixel) & 0x1);
            Serial.print(" numeral ");
            Serial.println(i);      
          } 
        }
      }      

      digitalWrite(matrixPin[matrix], LOW); // disable the current matrix, comment out to watch pixels blink out
      
      if (debug > 0) {
        Serial.print("Pin ");
        Serial.print(matrix);
        Serial.println(" reconfigured.");
      }
    }
*/
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

void writeNumeral(int selMatrix, int numGlyph){
  digitalWrite(pixelPin[pixel], ((numberGlyphs[numGlyph] >> pixel) & 0x1));
}
          if (debug > 1) {
            Serial.print("pixel ");
            Serial.print(pixel);
            Serial.print(" matrix ");
            Serial.print(matrix);
            Serial.print(" state ");
            Serial.print((numberGlyphs[pixelSelect % 10] >> pixel) & 0x1);
            Serial.print(" numeral ");
            Serial.println(i);      
          } 
  
}
