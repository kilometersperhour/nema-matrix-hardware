int out_row[15] = {40, 39, 38, 37, 26, 35, 34, 33, 32, 31, 15, 14, 13, 12, 11};
int out_col[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int out_row_len = 15;
int out_col_len = 8;

void setup() {
  // put your setup code here, to run once:
  // for (int i = 0; i < out_row_len; i++) {
    pinMode(40, OUTPUT);
    digitalWrite(40, HIGH);
    delay(1000);
  for (int i = 0; i < out_col_len; i++) {
    pinMode(out_col[i], OUTPUT);
    digitalWrite(out_col[i], HIGH);
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
