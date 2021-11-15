String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean pinState = 1;
int colSelect = 0;
int rowSelect = 0;

int rowPin[15] = {36, 35, 34, 33, 32, 31, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int colPin[8] = {19, 18, 17, 15, 14, 13, 12, 11};
int rowPinLen = 15;
int colPinLen = 8;

boolean debugSerial = false; // enable = true; use to view string at different stages


void setup() {
  // initialize serial:
  Serial.begin(9600);
  delay(350);
  Serial.println("Serial connection initialized.");
  inputString.reserve(200);

  // Set all pins in use to low for initialization test
  for (int i = 0; i < rowPinLen; i++) {
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], LOW);
  }
  for (int j = 0; j < colPinLen; j++) {
    pinMode(colPin[j], OUTPUT);
    digitalWrite(colPin[j], LOW);
  }

  // test configuration of LED arrays
  for (int i = 0; i < rowPinLen; i++) {
    digitalWrite(rowPin[i], HIGH);
    for (int j = 0; j < colPinLen; j++) {
      digitalWrite(colPin[j], HIGH);
      delay(500);
    }
    for (int j = 0; j < colPinLen; j++) {
      digitalWrite(colPin[j], LOW);
    }
    digitalWrite(rowPin[i], LOW);
    delay(2500);
  }


  // Set all pins in use to low so they don't float or anything
  for (int i = 0; i < rowPinLen; i++) {
    digitalWrite(rowPin[i], LOW);
  }
  for (int j = 0; j < colPinLen; j++) {
    digitalWrite(colPin[j], LOW);
  }

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
