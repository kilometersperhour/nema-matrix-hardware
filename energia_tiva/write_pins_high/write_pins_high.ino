// These includes from gpio_jtag example, with modified code included
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

int rowPin[22] = {28, 27, 26, 25, 24, 23, 8, 5, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 11, 12, 13, 17};
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
    if (i == 0) {
      //
      // Change PB6 to GPIO inputs. First open the lock and select
      // the bits we want to modify in the GPIO commit register.
      //
      HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
      HWREG(GPIO_PORTB_BASE + GPIO_O_CR) = 0x40;

      //
      // Now modify the configuration of the pins that we unlocked.
      // Note that the DriverLib GPIO functions may need to access
      // registers protected by the lock mechanism so these calls should
      // be made while the lock is open here.
      //
      HWREG(GPIO_PORTB_BASE + GPIO_O_AFSEL) &= 0x40;
      ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,
                               (GPIO_PIN_6));

      //
      // Finally, clear the commit register and the lock to prevent
      // the pin configuration from being changed accidentally later.
      // Note that the lock is closed whenever we write to the GPIO_O_CR
      // register so we need to reopen it here.
      //
      HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
      HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = 0x00;
      HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = 0;
    } 
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
//  for (int i = 0; i < rowPinLen; i++) {
    Serial.print("Setting pin ");
//    Serial.print(rowPin[i]);
    Serial.print(rowPin[21]);
    Serial.println(" to be LOW.");
//    pinMode(rowPin[i], OUTPUT);
//    digitalWrite(rowPin[i], LOW);
    digitalWrite(rowPin[21], LOW);
    delay(delayTime);
    Serial.print("Wait on pin ");
//    Serial.print(rowPin[i]);
    Serial.print(rowPin[21]);
    Serial.println(" complete.");
//  }
//  for (int i = 0; i < colPinLen; i++) {
    Serial.print("Setting pin ");
//    Serial.print(colPin[i]);
    Serial.print(colPin[2]);
    Serial.println(" to be LOW.");
//    pinMode(colPin[i], OUTPUT);
//    digitalWrite(colPin[i], LOW);
    digitalWrite(colPin[2], LOW);
    delay(delayTime);
    Serial.print("Wait on pin ");
//    Serial.print(colPin[i]);
    Serial.print(colPin[2]);
    Serial.println(" complete.");
//  }
  
//  for (int i = 0; i < rowPinLen; i++) {
    Serial.print("Setting pin ");
//    Serial.print(rowPin[i]);
    Serial.print(rowPin[21]);
    Serial.println(" to be HIGH.");
//    pinMode(rowPin[i], OUTPUT);
//    digitalWrite(rowPin[i], HIGH);
    digitalWrite(rowPin[21], HIGH);
    delay(delayTime);
    Serial.print("Wait on pin ");
//    Serial.print(rowPin[i]);
    Serial.print(rowPin[21]);
    Serial.println(" complete.");
//  }
//  for (int i = 0; i < colPinLen; i++) {
    Serial.print("Setting pin ");
//    Serial.print(colPin[i]);
    Serial.print(colPin[2]);
    Serial.println(" to be HIGH.");
//    pinMode(colPin[i], OUTPUT);
//    digitalWrite(colPin[i], HIGH);
    digitalWrite(colPin[2], HIGH);
    delay(delayTime);
    Serial.print("Wait on pin ");
//    Serial.print(colPin[i]);
    Serial.print(colPin[2]);
    Serial.println(" complete.");
//  }
}
