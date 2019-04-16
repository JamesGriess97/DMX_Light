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

    //extern button_t buttons[];
    //extern button_t *up, *down, *enter, *menu;
    void BUTTONS_init();
    void BUTTONS_task();
#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

