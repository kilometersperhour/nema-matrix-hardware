/*
Miles Martin

This code was initially written to update GPIO voltage levels to toggle LEDs in an LED matrix.
The intention was to display decimal glyphs on a minimal test-bench of 8 LEDs with a relocatable
ground connection, used to verify the output of the matrix row-by-row. This was not a suitable 
configuration for multiplexing at the scale of the project, but it inspired a great deal of 
the later code responsible for multiplexing the display in the design review as presented 
during finals week of December 2021.

Due to a misconfiguration and misunderstanding of the testbench hardware configuration. 
Some LEDs were dimmer than other lookalikes, and as a result, time was spent troubleshooting 
that hardware rather than the software driving it. Ultimately the assortment of LEDs had some 
that were just dim under the same load and nothing was wrong. This led to the reconfiguration 
of the code to perform serial writes instead of GPIO toggles, to ensure nothing was 
algorithmically incorrect on the software side.
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

  
int out_row[15] = {40, 39, 38, 37, 26, 35, 34, 33, 32, 31, 15, 14, 13, 12, 11};
int out_col[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int out_row_len = 15;
int out_col_len = 8;
int waittime = 60*1000/(out_row_len * out_col_len);

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
long zero  = (B00000110 << 24) + (B10011001 << 16) + (B10011001 << 8) + B10010110; // little endian nybbles, L to R, most sig. to least sig.
long one   = (B00000010 << 24) + (B00100010 << 16) + (B00100010 << 8) + B00100010;
long two   = (B00001111 << 24) + (B10000100 << 16) + (B00100001 << 8) + B10010110;
long three = (B00000110 << 24) + (B10010001 << 16) + (B00100001 << 8) + B10010110;
long four  = (B00000001 << 24) + (B00011111 << 16) + (B10010101 << 8) + B00110001;
long five  = (B00000110 << 24) + (B10010001 << 16) + (B00011110 << 8) + B10001111;
long six   = (B00000110 << 24) + (B10011001 << 16) + (B11101000 << 8) + B10000110;
long seven = (B00001000 << 24) + (B10000100 << 16) + (B00100001 << 8) + B00011111;
long eight = (B00000110 << 24) + (B10011001 << 16) + (B01101001 << 8) + B10010110;
long nine  = (B00000110 << 24) + (B00010001 << 16) + (B01111001 << 8) + B10010110;
  
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
          Serial.print("⚫ ");
        } 
        else {
          Serial.print("⚪ ");
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
