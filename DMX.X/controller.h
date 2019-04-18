/* 
 * File:   controller.h
 * Author: User
 *
 * Created on April 16, 2019, 4:32 PM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>

void CONTROLLER_task();
void CONTROLLER_init();
extern uint16_t address;
#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLLER_H */

