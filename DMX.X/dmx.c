#include <xc.h>

int dmxPointer = 0;
char dmxData[513];

void DMX_ISR(void) {
        LATB6 = 1;
        LATB6 = 0;
    if (RC1STAbits.FERR) {
        // set the pointer back to zero
        dmxPointer = 0;
    } else { 
        dmxPointer++;
    }
    dmxData[dmxPointer] = RC1REG;

    if (RC1STAbits.OERR) {
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    // or set custom function using EUSART1_SetRxInterruptHandler()
}

