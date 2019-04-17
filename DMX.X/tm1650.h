/* 
 * File:   tm1650.h
 * Author: Owner
 *
 * Created on March 25, 2019, 6:16 PM
 */

#ifndef TM1650_H
#define	TM1650_H

#ifdef	__cplusplus
extern "C" {
#endif

void TM1650_fastPrintNum(uint16_t);
void TM1650_setDigit(uint8_t, char, int);
void TM1650_init();

#ifdef	__cplusplus
}
#endif

#endif	/* TM1650_H */
