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
  if (debug) {
    Serial.begin(57600);
  }
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

    for (int i = 0; i < 10; i++) { // index max of 10 because there are 10 glyphs
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





  /*  static byte prevPixel = 0; // possibly useful for efficiency
    for (int pixel = 0; pixel < pixelPinLen; pixel++) {
      //  static byte prevMatrix; // possibly useful for efficiency

      for (int i = 0; i < matrixPinLen; i++) { // Disable matrix
        digitalWrite(matrixPin[i], LOW);
        //delay(1000);
        digitalWrite(pixelPin[prevPixel], LOW); // Disable pixel afterward

        digitalWrite(matrixPin[i], HIGH);    // enable matrix again
        digitalWrite(pixelPin[pixel], HIGH);    // enable new



        }


      delay(50);
      }
    }

    //delay(1);*/
}

void fillFramebuffer(uint32_t first, uint32_t second, uint32_t third, uint32_t fourth) {



}
