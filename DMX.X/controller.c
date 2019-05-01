#define SCROLL_SPEED 35

#include "controller.h"
#include "buttons.h"
#include "clock.h"
#include "tm1650.h"
#include <stdio.h>
#include <stdbool.h>

void numControl_init(int *val) {
    TM1650_fastPrintNum(*val);
}

/**
 * Increments the address and updates the display
 */
void increment(int *val)
{
    if(*val == 512) {
        *val = 1;
    } else {
        (*val)++;
    }
    TM1650_fastPrintNum(*val);
}

/**
 * Decrements the address and updates the display
 */
void decrement(int *val) 
{
    if(*val == 1) {
        *val = 512;
    } else {
        (*val)--;  
    }
    TM1650_fastPrintNum(*val);
}

static time_t lastTime = 0;
time_t lastActiveTime;
/**
 * handles number scrolling for DMX input
 */
 void numControl_Set(int *val) {
    time_t time = CLOCK_getTime();

    if (time - lastTime < SCROLL_SPEED)
        return;
    lastTime = time;
    
    if (BUTTONS_isClicked(up)) {
        increment(val);
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
