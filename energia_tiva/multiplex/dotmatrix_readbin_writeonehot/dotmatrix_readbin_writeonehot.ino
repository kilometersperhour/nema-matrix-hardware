/*
   To-dos:
      Create framebuffer manager
      Error checking
      Move away from globals
      Change variables to smaller types
      Add better comments
*/

boolean pinState = 1;
int matrixSelect = 0;
int pixelSelect = 0;
int pixelPin[22] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 39, 38, 40, 11, 12, 13, 17};
int matrixPin[4] = {14, 15, 18, 19};
int pixelPinLen = 22;
int matrixPinLen = 4;

int debug = 0;

uint32_t matrixFramebufferMask[4] = {(B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111}; //
uint32_t matrixFramebuffer[4] =  {((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00100001 << 16) + (B00100000 << 8) + B01001000), // one
                                 };

void setup() {
  // put your setup code here, to run once:

  String inputString = ""; // a string to hold incoming data
  boolean stringComplete = false; // whether the string is complete
  boolean pinState = 1;
  int matrixSelect = 0;
  int pixelSelect = 0;

  char outputString[100];

  Serial.begin(115200);
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

int waittime = 4; // 4ms = <62.5Hz/display, 25% duty cycle

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
uint32_t zero = (B00000000 << 24) + (B00010011 << 16) + (B01100100 << 8) + B11010110;
uint32_t one = (B00000000 << 24) + (B00010100 << 16) + (B00010010 << 8) + B00100100;
uint32_t two = (B00000000 << 24) + (B00111010 << 16) + (B10010000 << 8) + B01010110;
uint32_t three = (B00000000 << 24) + (B00010011 << 16) + (B00010000 << 8) + B01010110;
uint32_t four = (B00000000 << 24) + (B00100001 << 16) + (B11100101 << 8) + B01101000;
uint32_t five = (B00000000 << 24) + (B00010011 << 16) + (B00100011 << 8) + B10011111;
uint32_t six = (B00000000 << 24) + (B00010011 << 16) + (B01011100 << 8) + B10010110;
uint32_t seven = (B00000000 << 24) + (B00001010 << 16) + (B10010000 << 8) + B01001111;
uint32_t eight = (B00000000 << 24) + (B00010011 << 16) + (B01011000 << 8) + B11010110;
uint32_t nine = (B00000000 << 24) + (B00010001 << 16) + (B00111000 << 8) + B11010110;

uint32_t numberGlyphs[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

void loop() {
  // put your main code here, to run repeatedly:

  while (1) { // big loop
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
        pixelSelect = (10 * (inputString.charAt(0) - '0') + (inputString.charAt(1) - '0'));
      }
      inputString = inputString.substring(1);
      sprintf(outputString, "Setting LED at (%d,%d) to state %d.\n", matrixSelect, pixelSelect, pinState);
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
      pinConfigurator(pinState, matrixSelect, pixelSelect);
      Serial.println("Pin reconfigured.");

      Serial.println();
      // clear the string:
      inputString = "";
      stringComplete = false;
    }
    for (int matrix = 3; matrix < matrixPinLen; matrix++) { // per-matrix drawing loop
      digitalWrite(matrixPin[matrix], HIGH); // disable the current matrix, comment out to watch pixels blink out

      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel deactivation loop
        digitalWrite(pixelPin[pixel], LOW); // Disable pixel by pixel, clean slate
      }

      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel drawing loop
        // This is a pixel-light-setting loop to enable new matrix lights.
        // (7-0) grabs MSB and matrixPin[i] places it at (0,y), for example
        //          digitalWrite(pixelPin[pixel], (matrixFramebuffer[matrix] >> pixel) & 0x1);
        digitalWrite(pixelPin[pixel], ((numberGlyphs[i] >> pixel) & 0x1));
        if (debug > 1) {
          Serial.print("pixel ");
          Serial.print(pixel);
          Serial.print(" matrix ");
          Serial.print(matrix);
          Serial.print(" state ");
          Serial.print((numberGlyphs[i] >> pixel) & 0x1);
          Serial.print(" numeral ");
          //            Serial.println((matrixFramebuffer[matrix] >> pixel) & 0x1);
          Serial.println(i);
        }

      }
      delay(1000);
      digitalWrite(matrixPin[matrix], LOW); // disable the current matrix, comment out to watch pixels blink out
      //delay(1);
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
}
