/* 
 * File:   DMX_LED.h
 * Author: Owner
 *
 * Created on April 13, 2019, 4:38 PM
 */

#ifndef DMX_LED_H
#define	DMX_LED_H

#ifdef	__cplusplus
extern "C" {
#endif

void DMX_LED_Init();
void DMX_LED_SetColor(uint8_t, uint8_t, uint8_t, uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* DMX_LED_H */

