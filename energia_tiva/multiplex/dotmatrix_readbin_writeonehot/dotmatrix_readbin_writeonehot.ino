/*
 * To-dos: 
 *    Create framebuffer manager
 *    Error checking
 *    Move away from globals
 *    Change variables to smaller types
 *    Add better comments
 */

boolean pinState = 1;
int colSelect = 0;
int rowSelect = 0;

int rowPin[15] = {36, 35, 34, 33, 32, 31, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int colPin[8] = {19, 18, 17, 15, 14, 13, 12, 11};
int rowPinLen = 15;
int colPinLen = 8;

void setup() {
  // put your setup code here, to run once:

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

  
int out_row[15] = {40, 39, 38, 37, 26, 35, 34, 33, 32, 31, 15, 14, 13, 12, 11};
int out_col[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int out_row_len = 15;
int out_col_len = 8;
int waittime = 60*1000/(out_row_len * out_col_len);

// all possible LEDs, one bit per LED, one byte per row
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
                                 B11111111};

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
  //for (byte i = 0; i < out_row_len; i++) {
  //  for (byte j = 0; j < out_col_len; j++) {
  //    
  //    }
  //  }
  for (int row = 0; row < 15; row++) {
    static byte prevRow = 0; // possibly useful for efficiency
  //  static byte prevCol; // possibly useful for efficiency
  
    for (int i = 0; i < 8; i++) { // Disable column
      digitalWrite(colPin[i], LOW);
      //delay(1000); 
    } 
    digitalWrite(rowPin[prevRow], LOW);                                // Disable row afterward
    digitalWrite(rowPin[row], HIGH);                         // enable new row
    // row-light-setting loop to enable new col lights. 7-0 grabs MSB and colPin[i] places it at (0,y)
    for (int i = 0; i < 8; i++) { 
      digitalWrite(colPin[i], (framebuffer[row] >> i) & 0x1);
      //delay(1000);
    }
    prevRow = row;
    delay(67);
  }
  //delay(1);
}

void fillFramebuffer(uint32_t first, uint32_t second, uint32_t third, uint32_t fourth) {

  
  
}
