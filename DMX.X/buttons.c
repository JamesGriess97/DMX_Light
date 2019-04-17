#define BUTTON_SCAN_INTERVAL 50
#define BUTTON_COUNT 4
#define HOLD_TIME 500

#include <stdint.h>
#include <xc.h>

#include "buttons.h"
#include "clock.h"

button_t buttons[BUTTON_COUNT];
button_t *up, *down, *enter, *menu;

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin) {
    btn->port = port;
    btn->pin = pin;
    btn->state = STATE_UNPRESSED;
    btn->event = EVENT_IDLE;
}

void BUTTONS_init() {
    menu = &buttons[0];
    up = &buttons[1];
    down = &buttons[2];
    enter = &buttons[3];

    init(menu, &PORTC, 2);
    init(enter, &PORTA, 2);
    init(down, &PORTC, 0);
    init(up, &PORTC, 1);
}

int lastTime = 0;
void BUTTONS_task() {
    time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < BUTTON_SCAN_INTERVAL)
        return;

    lastTime = time;

    // walk through the list of buttons and update everything
    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        button_t* btn = buttons + i;
        
        // figure out if the button is currently activated or not
        if ((*(btn->port) & (1 << (btn->pin))) == 0) {
            btn->state = STATE_PRESSED;
        } else {
            btn->state = STATE_UNPRESSED;
        }

        if (btn->state == STATE_UNPRESSED && btn->lastState == STATE_PRESSED) {
            // we released the button
            btn->event = EVENT_PRESSED;
        } else if (btn->state == STATE_PRESSED && btn->lastState == STATE_PRESSED){
            // button still pressed
            volatile dif = time - btn->pressTime;
            if(dif > HOLD_TIME) {
                btn->event = EVENT_HELD;
            }
        } else if (btn->state == STATE_PRESSED && btn->lastState == STATE_UNPRESSED){
            btn->pressTime = time;
        }
        
        btn->lastState = btn->state;
    }
}

int BUTTONS_isClicked(button_t* button) {
    if (button->event == EVENT_PRESSED) {
        button->event = EVENT_IDLE;
        return 1;
    }
    return 0;
}

int BUTTONS_isHeld(button_t* button) {
    if (button->event == EVENT_HELD) {
        return 1;
    }
    
    return 0;
}

