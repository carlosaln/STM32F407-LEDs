/*  Input Handlers
   Author: Carlos Lemus
   Provides handlers for systick, external interrupt 0, and supervisory call
   interrupts
 */
#include "interrupt_handlers.h"
#include "main.h"

volatile uint16_t tick;

// stage of animation
volatile uint8_t stage = 0;
// order of counterclockwise mode
volatile uint8_t ccwise[] = {ORANGE_LED, GREEN_LED, BLUE_LED, RED_LED};
// order of clockwise mode
volatile uint8_t cwise[] = {ORANGE_LED, RED_LED, BLUE_LED, GREEN_LED};
// supervisory call used by SysTickHandler
void __svc(0x00) update_leds(void);

// updates LEDs to a new status every 500ms according to animation mode.
void SysTick_Handler (void)
{
        tick++;
        //switch statement allows for future time-based actions.
        switch (tick)
        {
        case 500:
                tick = 0;
                // make supervisory call
                update_leds();
        }
}


// clears flag and calls input handler to update status of button
void EXTI0_IRQHandler(void)
{
        NVIC_ClearPendingIRQ(EXTI3_IRQn);
        EXTI->PR |= (1<<0);
        input_handler();
}

// performs animation or turns LEDs off depending on mode and stage.
void SVC_Handler(void)
{
        int currentLED;
        // either button is pressed or last stage reached
        if (pressed == BUTTON_PRESSED || stage == 4)
        {
                stage = 0;
                pressed = 0;
                //clear leds
                for (currentLED = GREEN_LED; currentLED <= BLUE_LED; currentLED++)
                {
                        led_off(currentLED);
                }
        }
        //
        else if (mode == 2)
        {
                led_on(ccwise[stage]);
                stage++;
        }
        else if (mode == 3)
        {
                led_on(cwise[stage]);
                stage++;
        }
}
