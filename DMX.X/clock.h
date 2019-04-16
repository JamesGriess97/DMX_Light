/* 
 * File:   clock.h
 * Author: User
 *
 * Created on April 16, 2019, 12:44 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include <stdint.h>
    
typedef uint16_t time_t;

void CLOCK_init();
time_t CLOCK_getTime();

#endif	/* CLOCK_H */

