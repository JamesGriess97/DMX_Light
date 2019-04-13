#include "DMX_LED.h"

void DMX_LED_Init() {
    //WPUB7 = 1;
    
    TRISC7 = 0; // red
    TRISC6 = 0; // green
    TRISC4 = 0; // white
    TRISC3 = 0; // blue
    
    T2CLKCON = 0x01; // see Table 27-1 for details
    T2CONbits.ON = 1; // turn on Timer2

    CCP1CONbits.CCP1EN = 1;
    CCP1CONbits.MODE = 0b1100;
    CCP2CONbits.CCP2EN = 1;
    CCP2CONbits.MODE = 0b1100;
    CCP3CONbits.CCP3EN = 1;
    CCP3CONbits.MODE = 0b1100;
    CCP4CONbits.CCP4EN = 1;
    CCP4CONbits.MODE = 0b1100;
    
    
    RC7PPS = 0x09; // CCP1
    RC6PPS = 0x0A; // CCP2
    RC4PPS = 0x0B; // CCP3
    RC3PPS = 0x0C; // CCP4   
}

void DMX_LED_SetColor(uint8_t red, uint8_t green, uint8_t white, uint8_t blue) {
    red/=2;
    green/=2;
    blue/=2;
    white/=2;
    int hi1 = (red & 0xFF00) >> 8;
    int lo1 = red & 0x00FF;
    int hi2 = (green & 0xFF00) >> 8;
    int lo2 = green & 0x00FF;
    int hi3 = (blue & 0xFF00) >> 8;
    int lo3 = blue & 0x00FF;
    int hi4 = (white & 0xFF00) >> 8;
    int lo4 = white & 0x00FF;
    
    CCPR1H = hi1;
    CCPR1L = lo1;
    
    CCPR2H = hi2;
    CCPR2L = lo2;
    
    CCPR3H = hi3;
    CCPR3L = lo3;
    
    CCPR4H = hi4;
    CCPR4L = lo4;
}
