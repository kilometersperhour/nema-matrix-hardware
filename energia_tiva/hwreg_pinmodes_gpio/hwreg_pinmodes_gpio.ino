#include <stdint.h>
#include "inc/hw_gpio.h"

void setup() {
  HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = 0x0F;

  //
  // Now modifiy the configuration of the pins that we unlocked.
  // Note that the DriverLib GPIO functions may need to access
  // registers protected by the lock mechanism so these calls should
  // be made while the lock is open here.
  //
  HWREG(GPIO_PORTC_BASE + GPIO_O_AFSEL) &= 0xf0;
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,
                           (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                            GPIO_PIN_3));

  //
  // Finally, clear the commit register and the lock to prevent
  // the pin configuration from being changed accidentally later.
  // Note that the lock is closed whenever we write to the GPIO_O_CR
  // register so we need to reopen it here.
  //
  HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = 0x00;
  HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = 0;}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
