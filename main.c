/* Main Program
	Author: Carlos Lemus
	The main program does the following:
 	(1) configures the Button and LEDs
	(2) initializes the mode and pressed variables.
	(3) holds the program in an infinite loop, waiting for interrupts to act.
*/

#include <stdio.h>
#include "STM32F4xx.h"
#include "main.h"

volatile uint32_t mode;
volatile uint32_t pressed;

void Button_Initialize(void)
{
		//set PA0 to digital input mode
		GPIOA->MODER &= ~(GPIO_MODER_MODER0);
		//enable clock for GPIOA
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		//pull-up pin 0
		GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;

		/** SETTING BUTTON AS AN INTERRUPT **/
		// 1. Configure the SYSCFG module to choose PA0
		SYSCFG->EXTICR[0] &= SYSCFG_EXTICR1_EXTI0_PA;

		// 2. Configure EXTI module to enable interrupt on rising trigger
		EXTI->IMR |= (1<<0);
		EXTI->RTSR |= (1<<0);

		// 3. Enable interrupt at CPU
		__enable_irq();

		// 4. Set priority in NVIC, clear pending flag, enable interrupt
		NVIC_SetPriority(EXTI0_IRQn,0);
		NVIC_ClearPendingIRQ(EXTI0_IRQn);
		NVIC_EnableIRQ(EXTI0_IRQn);
}

void LED_Initialize(void)
{
		// enable clock for GPIOD
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

		// clear any previous modes for pins 12-15
		GPIOD->MODER &= ~(GPIO_MODER_MODER12 |
						GPIO_MODER_MODER13	|
						GPIO_MODER_MODER14	|
						GPIO_MODER_MODER15 );

					// set mode to output for pins 12-15
		GPIOD->MODER |= (GPIO_MODER_MODER12_0 |
			GPIO_MODER_MODER13_0	|
			GPIO_MODER_MODER14_0	|
			GPIO_MODER_MODER15_0	);
}

int main(void) {
		mode = COUNTERCLOCKWISE;
		pressed = BUTTON_NOT_PRESSED;

		SystemCoreClockUpdate();
		SysTick_Config(SystemCoreClock / 1000);

		//initialize LEDs and set them to output
		LED_Initialize();
		//initialize button and set it as interrupt
		Button_Initialize();

		//loop forever, interrupts will take care of all.
		while(1);
}
