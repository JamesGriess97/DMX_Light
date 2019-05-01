/**
#define SCROLL_SPEED 35

#include "controller.h"
#include "buttons.h"
#include "clock.h"
#include "tm1650.h"
#include <stdio.h>
#include <stdbool.h>


 * Increments the address and updates the display
void increment(int *val)
{
    if(*val == 512) {
        *val = 1;
    } else {
        (*val)++;
    }
    // update the display
    TM1650_fastPrintNum(*val);
}

 */
/**
 * Decrements the address and updates the display
void decrement(int *val) 
{
    if(*val == 1) {
        *val = 512;
    } else {
        (*val)--;  
    }
    
    // update the display
    TM1650_fastPrintNum(*val);
}
 */

/**
static time_t lastTime = 0;
time_t lastActiveTime;
 * handles number scrolling for DMX input
 void dispInc(int *val) {
     volatile int *foo = val;
     volatile int doo = *foo;
    time_t time = CLOCK_getTime();

    if (time - lastTime < SCROLL_SPEED)
        return;
    lastTime = time;
    
    if (BUTTONS_isClicked(up)) {
        increment(foo);
        lastActiveTime = time;
        TM1650_enable(true);
    } else if (BUTTONS_isClicked(down)) {
        decrement(val);
        lastActiveTime = time;
        TM1650_enable(true);
    } else {
        if (CLOCK_getTime() - lastActiveTime >= 5000) {
            TM1650_enable(false);
            lastActiveTime = CLOCK_getTime() - 5001;
        }
    }
}

 */
