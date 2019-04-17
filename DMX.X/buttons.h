/* 
 * File:   buttons.h
 * Author: User
 *
 * Created on April 16, 2019, 4:32 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
    
    typedef enum {
        EVENT_IDLE,
        EVENT_PRESSED
    } event_t;

    typedef enum {
        STATE_UNPRESSED,
        STATE_PRESSED
    } btnState_t;

    typedef struct {
        volatile uint8_t* port;
        uint8_t pin;
        btnState_t state;
        btnState_t lastState;
        event_t event;
    } button_t;

    
    //extern button_t buttons[];
    extern button_t *up, *down, *enter, *menu;
    void BUTTONS_init();
    void BUTTONS_task();
    int BUTTONS_isClicked(button_t*);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

