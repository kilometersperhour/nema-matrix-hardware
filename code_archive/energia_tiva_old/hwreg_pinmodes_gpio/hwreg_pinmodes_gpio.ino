/*
  This code uses lines from the "gpio_jtag_example" previously described. 
  The portion referenced is found within the function GPIOJTAGTestCallback(), where internal 
  registers of the Tiva C Launchpad board are set, cleared, or reset to provide alternate 
  functions to pins such as the JTAG pins, as demonstrated here. An alternate function of the 
  JTAG pins is to function as GPIO, as might be used in this project. This sample of code was
  considered possibly helpful because the high output voltage of certain pins on the 
  microcontroller board was not consistently the logic-high 3.3V expected. This manifested on 
  on the LED matrix as dimly/barely toggling the gate of the transistors controlling lighting
  the LEDs of the matrix. For example, a 1V output was still within the small-signal range of 
  the NMOS transistors used in this project, so the LED barely responded to the toggling of 
  such pins. It has not yet been determined whether the following code would be helpful in 
  providing the solution needed (logic-high voltages at ther nominal values for all utilized 
  pins), but it does provide a possible explanation for the board's shortcomings, as GPIO is
  universally assignable using the Arduino Language's function pinMode() function; the 
  edge-case is not handled by the pinMode function or the library code for the Tiva C Launchpad
  board and must be manually handled for these exceptional pins.
 
  The code has been modified to (in theory) affect the operation of pins on the C register, 
  which at the time of testing, were not producing the nominal logic-high voltage used to toggle
  transistor gates in this project.
*/

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
