#include "mcc_generated_files/mcc.h"
#include "clock.h"
#include "tm1650.h"
#include "buttons.h"
#include "controller.h"
#include "beat.h"
#include "dmx.h"
#include "led.h"

/*
                         Main application
 */


void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    CLOCK_init();
    TRISB6 = 0;
    LATB6 = 0;
    EUSART1_SetRxInterruptHandler(DMX_ISR);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
     __delay_ms(500);
    TM1650_init();
    BUTTONS_init();
    CONTROLLER_init();
    initLED();
    BEAT_init();

    while (1) {
        // Add your application code
        BEAT_task();
        LED_task();
        BUTTONS_task();
        CONTROLLER_task();    
        DMX_task();
    }
}