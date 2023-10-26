# Classpert Week 5: Make a console

## Goal
Using a STM32 dev board to control inputs, outputs and timers

## Hardware
The hardware used for this excercise is a STM32F407G-DISC1 board with an STM32F407 controller.

### Hardware block diagram
![Hardware block diagram](https://github.com/dmeprojects/Classpert_GreenTurtles/blob/main/Week%203/images/BlockDiagram_LEDBLINK.png)

### Software
The software contains 3 LED patterns.  A button is used to switch between the patterns.

## Questions
### What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.)

To change the state of a pin, we need to configure the port pin as an output device. 

If all this is done, we can use the GPIO port bit set/reset register to toggle the pin.  This register contains 32 bits, the highest 16 bits are to reset a pin.  Writing a "1" to the corresponding pin bit, we can turn of the LED.  If we want to turn the LED on, we can write a 1 to the lowest 16 bits of this register. Writing a "1" here to the corresponding pin bit will turn on the pin.
### What are the registers that you read in order to find out the state of the button?

To read an input, we need to read the GPIO input data register (GPIOx_IDR).  If the corresponding bit of our input pin reads "1", the input is high.
### Can you read the register directly and see the button change in a debugger or by printing out thes value of the memory at the register’s address?

If we look at the GPIO port input data register (GPIOx_IDR) of the corresponding port where our button has been connected, we can see the register value change when pressing the button.  