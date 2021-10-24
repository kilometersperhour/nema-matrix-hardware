void setup() {
  // put your setup code here, to run once:
  
  // these one-hot outputs encode/map to binary inputs
  int out_array[] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  // use to read binary input from UNO
  int in_array[] = {A4, A3, A2, A1}; 
  
  // find size for iteration/traversal
  int out_array_len[] = sizeof(out_array)/sizeof(out_array[0]);
  int in_array_len[] = sizeof(in_array)/sizeof(in_array[0]);
  
  // Set analog pins as digital inputs
  for (byte i = 0; i < in_array_len; i++) {
    pinMode(in_array[i], INPUT);
  }
  // set up digital outputs
  for (byte i = 0; i < out_array_len; i++) {
    pinMode(out_array[i], OUTPUT);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogRead();

}
