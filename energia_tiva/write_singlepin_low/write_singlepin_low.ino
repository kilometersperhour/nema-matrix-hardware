/*Miles Martin
This code was used when an unfortunate accident led to the inoperability 
of a specific pin (pin 27) on the microcontroller. The pin was stuck high
and caused an LED to stay on regardless of software configuration. 

This program, while very simple, helped eliminate the possibility that other
software might have been interfering with the function of the pin and causing 
it to be driven high, as opposed to the pin's functionality being destroyed by 
an electrical mistake. 

It was determined that pin 27 is not tolerant to +/-12V input.
*/

void setup() {
    pinMode(27, OUTPUT);
    digitalWrite(27, LOW);
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
