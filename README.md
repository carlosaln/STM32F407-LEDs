# STM32F407 LED Animation with User Button Interrupt Handler

A program to practice with parallel I/O ports that creates and displays one of two patterns (clockwise or counterclockwise) on the 4 LEDs on the Discovery board by using the user push button (the blue button). 

####Some Features in the Code
* Drivers for turning in LEDs on and off are written in assembly (output_handler.s)
* Animation is performed through a supervisory call every 500ms (input_handler.c)
* Initialization is done by configuring specific registers in main.c
