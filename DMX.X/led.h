/* 
 * File:   led.h
 * Author: User
 *
 * Created on April 29, 2019, 3:36 PM
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
struct RGB {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

struct HSL {
	int H;
	float S;
	float L;
};

void initLED();
void LED_DMX();
void LED_Beat();
void LED_setHSL(struct HSL);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

