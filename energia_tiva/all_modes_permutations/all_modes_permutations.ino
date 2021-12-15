
int pixelPin[22] = {28, 27, 26, 25, 24, 23, 8, 5, 31, 32, 33, 34, 35, 36, 37, 38, 3, 4, 11, 12, 13, 17}; // transpose 3 & 4?
//int matrixPin[4] = {14, 15, 18, 19};
int matrixPin[4] = {14, 15, 2, 19};
int pixelPinLen = 22;
int matrixPinLen = 4;
int delayTime = 500;

void setup() {
  // put your setup code here, to run once:
  int pixel = 3;
  int pixelState = OUTPUT;
  int matrix = 3;
  int matrixState = INPUT;
  Serial.begin(9600);

  for (int i = 0; i < pixelPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(pixelPin[i]);
    Serial.println(" to be OUTPUT.");
    pinMode(pixelPin[i], OUTPUT);
    digitalWrite(pixelPin[i], LOW);
    //    delay(delayTime);
  }
  for (int i = 0; i < matrixPinLen; i++) {
    Serial.print("Setting pin ");
    Serial.print(matrixPin[i]);
    Serial.println(" to be OUTPUT.");
    pinMode(matrixPin[i], OUTPUT);
    digitalWrite(matrixPin[i], LOW);
    //    delay(delayTime);
  }

  Serial.print("Matrix ");
  Serial.print(matrix);
  Serial.print(" to state ");
  Serial.println(matrixState);
  pinMode(matrixPin[matrix], OUTPUT);
  digitalWrite(matrixPin[matrix], HIGH);                           // enable new matrix

  for (int i = 0; i < 4; i++) {
    delay(2000);
    Serial.print("Pixel ");
    Serial.print(i);
    Serial.print(" to state ");
    Serial.println(HIGH);
    pinMode(pixelPin[i], OUTPUT);
    digitalWrite(pixelPin[i], HIGH);                         // enable new pixel
    delay(2000);
  }
}

void loop() {
}
