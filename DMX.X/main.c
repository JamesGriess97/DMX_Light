/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"
#include "clock.h"
#include "tm1650.h"
#include "buttons.h"
#include "controller.h"

/*
                         Main application
 */
void DMX_ISR();
void initLED();
void LED_setColor(uint8_t, uint8_t, uint8_t, uint8_t);

volatile char dmxData[513];
int dmxPointer = 0;

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


void Blink2() {
    static bool value = 0;
    static time_t lastTime = 0;
    
    time_t time = CLOCK_getTime();
    if(time <= lastTime + 51)
        return;
    
    lastTime = time;
    value = !value;
    
    if(value)
        TM1650_setDigit(1, '8', 0);
    else
        TM1650_setDigit(1, ' ', 0);
    
}

void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    initLED();
    CLOCK_init();
    TRISB6 = 0;
    LATB6 = 0;
    EUSART1_SetRxInterruptHandler(DMX_ISR);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    TM1650_init();
    BUTTONS_init();
    while (1) {
        // Add your application code
        //LED_setColor(dmxData[2], dmxData[3], dmxData[4], dmxData[5]);
        BUTTONS_task();
        //TM1650_setDigit(1, 'c', 0);
        
    }
}


void initLED() {
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


void LED_setColor(uint8_t red, uint8_t green, uint8_t white, uint8_t blue) {
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


/**
 End of File
 */