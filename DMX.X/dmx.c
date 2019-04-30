#define DMX_CHECK_TIME 1000

#include <xc.h>
#include <stdbool.h>
#include "clock.h"

int dmxPointer = 0;
char dmxData[513];
bool offCheck = false;
bool dmxOn = false;

    
void DMX_ISR(void) {
        LATB6 = 1;
        LATB6 = 0;
    if (RC1STAbits.FERR) {
        // set the pointer back to zero
        dmxPointer = 0;
        offCheck = true;
    } else { 
        dmxPointer++;
    }
    dmxData[dmxPointer] = RC1REG;
            
    if (RC1STAbits.OERR) {
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    // or set custom function using EUSART1_SetRxInterruptHandler()
}

static time_t lastTime = 0;
bool toggleCheck = false;

void DMX_task() {
    time_t time = CLOCK_getTime();
    if (time - lastTime < DMX_CHECK_TIME)
        return;
    lastTime = time;
    
    if(offCheck && !toggleCheck) {
        // first framing error
        toggleCheck = true;
        offCheck = false;
        return;
    }
    
    if (offCheck && toggleCheck) {
        dmxOn = true;
        toggleCheck = false;
        offCheck = false;
    } else {
        dmxOn = false;
    }
}

bool isDMXOn() {
    return dmxOn;
}