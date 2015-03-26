#ifndef _MAIN_H
#define	_MAIN_H

#define BUTTON_PRESSED 1
#define BUTTON_NOT_PRESSED 0

#define ORANGE_LED 13
#define GREEN_LED 12
#define RED_LED 14
#define BLUE_LED 15

#define COUNTERCLOCKWISE 1
#define CLOCKWISE 2

// global variables used to perform functions
extern volatile uint32_t mode;
extern volatile uint32_t pressed;

// updates status of button and avoids bounces
extern void input_handler(void);

// functions to turn LEDs on and off
extern void led_on(int pin);
extern void led_off(int pin);

#endif
