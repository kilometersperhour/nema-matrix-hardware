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
int pixelPin[22] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 3, 4, 40, 11, 12, 13, 17};
int matrixPin[4] = {14, 15, 18, 19};
int pixelPinLen = 22;
int matrixPinLen = 4;

int debug = 2;

uint32_t matrixFramebufferMask[4] = {(B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111}; //
uint32_t matrixFramebuffer[4] =  {((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00111111 << 16) + (B11111111 << 8) + B11111111),
                                  ((B00000000 << 24) + (B00100001 << 16) + (B00100000 << 8) + B01001000), // one
                                 };

void setup() {
  // put your setup code here, to run once:
  if (debug) {
    Serial.begin(1000000);
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


int out_pixel[15] = {40, 39, 38, 37, 26, 35, 34, 33, 32, 31, 15, 14, 13, 12, 11};
int out_matrix[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int out_pixel_len = 15;
int out_matrix_len = 8;
int waittime = 60 * 1000 / (out_pixel_len * out_matrix_len);

// all possible LEDs, one bit per LED, one byte per pixel
static byte framebuffer[15] =   {B00010001,
                                 B00100010,
                                 B00110011,
                                 B01000100,
                                 B01010101,
                                 B01100110,
                                 B01110111,
                                 B10001000,
                                 B10011001,
                                 B10101010,
                                 B10111011,
                                 B11001100,
                                 B11011101,
                                 B11101110,
                                 B11111111
                                };

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
uint32_t zero  = (B00000110 << 24) + (B10011001 << 16) + (B10011001 << 8) + B10010110; // little endian nybbles, L to R, most sig. to least sig.
uint32_t one   = (B00000010 << 24) + (B00100010 << 16) + (B00100010 << 8) + B00100010;
uint32_t two   = (B00001111 << 24) + (B10000100 << 16) + (B00100001 << 8) + B10010110;
uint32_t three = (B00000110 << 24) + (B10010001 << 16) + (B00100001 << 8) + B10010110;
uint32_t four  = (B00000001 << 24) + (B00011111 << 16) + (B10010101 << 8) + B00110001;
uint32_t five  = (B00000110 << 24) + (B10010001 << 16) + (B00011110 << 8) + B10001111;
uint32_t six   = (B00000110 << 24) + (B10011001 << 16) + (B11101000 << 8) + B10000110;
uint32_t seven = (B00001000 << 24) + (B10000100 << 16) + (B00100001 << 8) + B00011111;
uint32_t eight = (B00000110 << 24) + (B10011001 << 16) + (B01101001 << 8) + B10010110;
uint32_t nine  = (B00000110 << 24) + (B00010001 << 16) + (B01111001 << 8) + B10010110;

uint8_t numberBinary[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

uint32_t numberGlyphs[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
uint8_t serialOutput;

void loop() {
  // put your main code here, to run repeatedly:

  while (1) { // big loop


    for (int matrix = 3; matrix < matrixPinLen; matrix++) { // per-matrix drawing loop
      digitalWrite(matrixPin[matrix], HIGH); // disable the current matrix, comment out to watch pixels blink out

      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel deactivation loop
        digitalWrite(pixelPin[pixel], LOW); // Disable pixel by pixel, clean slate
      }

      for (int pixel = 0; pixel < pixelPinLen; pixel++) { // per-pixel drawing loop
        // This is a pixel-light-setting loop to enable new matrix lights.
        // (7-0) grabs MSB and matrixPin[i] places it at (0,y), for example
        digitalWrite(pixelPin[pixel], (matrixFramebuffer[matrix] >> pixel) & 0x1);
        if (debug>1) {
          Serial.print("pixel ");
          Serial.print(pixel);
          Serial.print(" matrix ");
          Serial.print(matrix);
          Serial.print(" state ");
          Serial.println((matrixFramebuffer[matrix] >> pixel) & 0x1);
        }
        
      }
      
      delay(4);
      digitalWrite(matrixPin[matrix], LOW); // disable the current matrix, comment out to watch pixels blink out
      //delay(1);
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
