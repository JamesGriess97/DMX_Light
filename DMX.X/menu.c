#define CYCLE_SPEED 20
#define PULSE_SPEED 400
#define SCROLL_SPEED 35

#include "led.h"
#include "beat.h"
#include "dmx.h"
#include "controller.h"
#include "clock.h"
#include "tm1650.h"
#include "buttons.h"

enum menu{DMXADR, BEAT, PATTERN}; 
int currentState = 0;
bool firstMsg = true;

void menuButtons() {
    if (BUTTONS_isClicked(menu)) {
        numControl_resetTimer();
        firstMsg = true;
        if(currentState == 2) {
            currentState = 0;
        } else {
            currentState += 1;
        }
    }
}

static time_t lastTimeCycle = 0;
int hueValCycle = 0;
int cycleSpeed = 20;
void cycleColors() {
    time_t time = CLOCK_getTime();

    if (time - lastTimeCycle < cycleSpeed)
        return;
    lastTimeCycle = time;
    numControl_Set(&cycleSpeed, 100, 1, 1);
    if(hueValCycle == 360) {
        hueValCycle = 0;
    } else {
        hueValCycle += 1;
    }
    struct HSL color = {hueValCycle, 1, .5};
    LED_setHSL(color);
}


static time_t lastTimePulse = 0;
float fadeTime = 0;
int pulseSpeed = 400;
int hueValPulse = 0;
struct HSL pulseColor = {0, 1, .5};
void pulseColors() {
    numControl_Set(&pulseSpeed, 600, 100, 10);

    if(fadeTime == -pulseSpeed/10) {
        //make a new pulse
        if(hueValPulse == 360) {
            hueValPulse = 0;
        } else {
            hueValPulse += 36;
        }
        pulseColor.H = hueValPulse;
        pulseColor.L = 1;
        fadeTime = pulseSpeed/2;
    } else if(fadeTime > 0) {
        pulseColor.L = fadeTime/(pulseSpeed);
        fadeTime -= 1;
    } else {
        fadeTime -= 1;
    }
    
    LED_setHSL(pulseColor);
}


void MENU_task() {
    if(isDMXOn()) {
        LED_DMX();
        numControl_Set(&address, 512, 1, 1);
    } else {
        menuButtons();
        if(currentState == 2) {
            TM1650_enable(false);
            LED_Beat();
            BEAT_task();
        } else if(currentState == 1) {
            if(firstMsg) {
                TM1650_enable(true);
                TM1650_setDigit(0, 'P', 0);
                TM1650_setDigit(1, 'L', 0);
                TM1650_setDigit(2, 'S', 0);
                TM1650_setDigit(3, 'E', 0);
                firstMsg = false;
            }
            pulseColors();
        } else if (currentState == 0) {
            if(firstMsg) {
                TM1650_enable(true);
                TM1650_setDigit(0, 'C', 0);
                TM1650_setDigit(1, 'Y', 0);
                TM1650_setDigit(2, 'C', 0);
                TM1650_setDigit(3, 'L', 0);
                firstMsg = false;
            }
            cycleColors();
        }

    }
}