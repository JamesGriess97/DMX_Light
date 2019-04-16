# 1 "controller.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "controller.c" 2
# 1 "./controller.h" 1
# 15 "./controller.h"
void CONTROLLER_task();
# 1 "controller.c" 2

# 1 "./buttons.h" 1
# 14 "./buttons.h"
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 135 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 150 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 166 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 196 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 237 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 155 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 155 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3
# 14 "./buttons.h" 2


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



    extern button_t *up, *down, *enter, *menu;
    void BUTTONS_init();
    void BUTTONS_task();
# 2 "controller.c" 2

# 1 "./clock.h" 1
# 11 "./clock.h"
typedef uint16_t time_t;

void CLOCK_init();
time_t CLOCK_getTime();
# 3 "controller.c" 2

# 1 "./tm1650.h" 1
# 15 "./tm1650.h"
void TM1650_setDigit(uint8_t, char, int);
void TM1650_init();
# 4 "controller.c" 2


uint16_t address = 1;

void CONTROLLER_init() {
    TM1650_fastPrintNum(address);
}




void address_inc()
{
    if(address == 512)
        address = 1;
    else
        address++;


    TM1650_fastPrintNum(address);
}




void address_dec()
{
    if(address == 1)
        address = 512;
    else
        address--;


    TM1650_fastPrintNum(address);
}

void CONTROLLER_task() {
    if (BUTTONS_isClicked(up)) {
        address_inc();

    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    }
}
