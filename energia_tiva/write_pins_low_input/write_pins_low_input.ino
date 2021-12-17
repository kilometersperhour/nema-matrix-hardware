/*Miles Martin

This code was used to test the effect of high input impedance of GPIO pins controlling the light-level
of LEDs on the LED matrix. 
*/

int rowPin[22] = {28, 27, 26, 25, 24, 23, 8, 5, 31, 32, 33, 34, 35, 36, 37, 38, 3, 4, 11, 12, 13, 17}; // transpose 3 & 4?
//int colPin[4] = {14, 15, 18, 19};
int colPin[4] = {14, 15, 2, 19};
int rowPinLen = 22;
int colPinLen = 4;
int delayTime = 500;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  for (int i = 0; i < rowPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(rowPin[i]);
    Serial.println(" to be INPUT.");
    pinMode(rowPin[i], INPUT);
//    digitalWrite(rowPin[i], LOW);
//    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(rowPin[i]);
    Serial.println(" complete.");
  }
  for (int i = 0; i < colPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(colPin[i]);
    Serial.println(" to be INPUT.");
    pinMode(colPin[i], INPUT);
//    digitalWrite(colPin[i], LOW);
//    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(colPin[i]);
    Serial.println(" complete.");
  }
  /*
  for (int i = 0; i < rowPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(rowPin[i]);
    Serial.println(" to be HIGH.");
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], HIGH);
    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(rowPin[i]);
    Serial.println(" complete.");
  }
  for (int i = 0; i < colPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(colPin[i]);
    Serial.println(" to be HIGH.");
    pinMode(colPin[i], OUTPUT);
    digitalWrite(colPin[i], HIGH);
    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(colPin[i]);
    Serial.println(" complete.");
    
  }
  */
}

void loop() {
}
