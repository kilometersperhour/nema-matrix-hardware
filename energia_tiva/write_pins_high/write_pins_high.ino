int rowPin[15] = {36, 35, 34, 33, 32, 31, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int colPin[8] = {19, 18, 17, 15, 14, 13, 12, 11};
int rowPinLen = 15;
int colPinLen = 8;
int delayTime = 500;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  for (int i = 0; i < rowPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(rowPin[i]);
    Serial.println(" to be LOW.");
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], LOW);
//    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(rowPin[i]);
    Serial.println(" complete.");
  }
  for (int i = 0; i < colPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(colPin[i]);
    Serial.println(" to be LOW.");
    pinMode(colPin[i], OUTPUT);
    digitalWrite(colPin[i], LOW);
//    delay(delayTime);
    Serial.print("Wait on pin ");
    Serial.print(colPin[i]);
    Serial.println(" complete.");
  }
  
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
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
