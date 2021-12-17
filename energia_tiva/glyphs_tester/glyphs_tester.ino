/*

This code was originally implemented to test the programmer's accuracy when manually defining
the binary-encoded decimal glyphs shown on the LED matrix used in the 2021-2022 senior 
capstone project of Miles Martin and Ally DiFilippo. 

Pin mappings and serial debug output are not representative of the final product and slow down
the execution of the program significantly, affecting multiplexing speed and quality.

This code, as written, writes serial output at 9600 baud, writing representations of each glyph over
the Serial Monitor built into the Energia IDE. An activated LED was represented by "o " 
whereas a deactivated LED was represented by two spaces ("  "). 
Line by line each glyph was printed. Sample output can be seen below:

00,3:   o o   
04,3: o     o 
08,3:       o 
12,3:     o   
16,3:       o 
20,3: o     o 
24,3:   o o   


The ordered pair (xx,y) at the beginning of the line represents:
	xx: the value of the iterator i for the duration of the row. This was displayed using two 
	place values because the number displayed here could be as large as 24.
	y: the numeral equivalent to the glyph being printed. Helpful to see if what is suppposed 
	to be displayed matches what would be represented by the glyph.


*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < out_row_len; i++) {
    pinMode(40, OUTPUT);
    digitalWrite(40, HIGH);
    delay(1000);
  for (int i = 0; i < out_col_len; i++) {
    pinMode(out_col[i], OUTPUT);
    digitalWrite(out_col[i], HIGH);
    delay(1000);
  }
}

  
int out_row[15] = {40, 39, 38, 37, 26, 35, 34, 33, 32, 31, 15, 14, 13, 12, 11};
int out_col[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int out_row_len = 15;
int out_col_len = 8;
int waittime = 60*1000/(out_row_len * out_col_len);

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
int zero  = (B00000110 << 24) + (B10011001 << 16) + (B10011001 << 8) + B10010110; // little endian nybbles, L to R, most sig. to least sig.
int one   = (B00000010 << 24) + (B00100010 << 16) + (B00100010 << 8) + B00100010;
int two   = (B00001111 << 24) + (B10000100 << 16) + (B00100001 << 8) + B10010110;
int three = (B00000110 << 24) + (B10010001 << 16) + (B00100001 << 8) + B10010110;
int four  = (B00000001 << 24) + (B00011111 << 16) + (B10010101 << 8) + B00110001;
int five  = (B00000110 << 24) + (B10010001 << 16) + (B00011110 << 8) + B10001111;
int six   = (B00000110 << 24) + (B10011001 << 16) + (B11101000 << 8) + B10000110;
int seven = (B00001000 << 24) + (B10000100 << 16) + (B00100001 << 8) + B00011111;
int eight = (B00000110 << 24) + (B10011001 << 16) + (B01101001 << 8) + B10010110;
int nine  = (B00000110 << 24) + (B00010001 << 16) + (B01111001 << 8) + B10010110;
  
int numberGlyphs[10] = {zero, one, two, three, four, five, six, seven, eight, nine};
int serialOutput;

void loop() {
  // put your main code here, to run repeatedly: 
  //for (byte i = 0; i < out_row_len; i++) {
  //  for (byte j = 0; j < out_col_len; j++) {
  //    
  //    }
  //  }
  for (int j = 0; j < 10; j = j + 1) {
    for (int i = 0; i < 28; i = i + 4) {
      if (i < 10) {
        Serial.print(0);
        Serial.print(i);
      } else {
        Serial.print(i);
      
      }
      Serial.print(",");
      Serial.print(j);
      Serial.print(": ");
      serialOutput = (numberGlyphs[j] >> i) & B1111;      
      for (int k = 3; k >= 0; k = k - 1) {
        if ((serialOutput & (0x1 << k))/(0x1 << k)) {
          Serial.print("o ");
        } 
        else {
          Serial.print("  ");
        };
      }
      Serial.println();
    }  
      Serial.println();
  }
  Serial.println();
  Serial.println();
  delay(10000);
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
