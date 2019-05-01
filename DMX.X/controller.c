#define SCROLL_SPEED 35

#include "controller.h"
#include "buttons.h"
#include "clock.h"
#include "tm1650.h"
#include <stdio.h>
#include <stdbool.h>

uint16_t address = 1;

void adrControl_init() {
    TM1650_fastPrintNum(address);
}

/**
 * Increments the address and updates the display
 */
void address_inc()
{
    if(address == 512) {
        address = 1;
    } else {
        address++;
    }
    
    // update the display
    TM1650_fastPrintNum(address);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() 
{
    if(address == 1) {
        address = 512;
    } else {
        address--;  
    }
    
    // update the display
    TM1650_fastPrintNum(address);
}

static time_t lastTime = 0;
time_t lastActiveTime;
/**
 * handles number scrolling for DMX input
 */
 void adrControl_DMX() {
    time_t time = CLOCK_getTime();

    if (time - lastTime < SCROLL_SPEED)
        return;
    lastTime = time;
    
    if (BUTTONS_isClicked(up)) {
        address_inc();
        lastActiveTime = time;
        TM1650_enable(true);
    } else if (BUTTONS_isClicked(down)) {
        address_dec();
        lastActiveTime = time;
        TM1650_enable(true);
    } else {
        if (CLOCK_getTime() - lastActiveTime >= 5000) {
            TM1650_enable(false);
            lastActiveTime = CLOCK_getTime() - 5001;
        }
    }
}
