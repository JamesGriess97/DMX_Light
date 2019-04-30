#define FADE_TIME 10
#define FADE_AMMOUNT 20

#include <xc.h>
#include <stdbool.h>
#include "led.h"
#include "beat.h"
#include "controller.h"
#include "clock.h"
#include "dmx.h"

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

float HueToRGB(float v1, float v2, float vH) {
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
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

void LED_setHSL(struct HSL hsl) {
	struct RGB rgb;

	if (hsl.S == 0)
	{
		rgb.R = rgb.G = rgb.B = (unsigned char)(hsl.L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)hsl.H / 360;

		v2 = (hsl.L < 0.5) ? (hsl.L * (1 + hsl.S)) : ((hsl.L + hsl.S) - (hsl.L * hsl.S));
		v1 = 2 * hsl.L - v2;

		rgb.R = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
		rgb.G = (unsigned char)(255 * HueToRGB(v1, v2, hue));
		rgb.B = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
	}

	LED_setColor(rgb.R, rgb.G, rgb.B, 0);
}

extern char dmxData[513];
static time_t lastTime = 0;

int fadeAmmount = FADE_AMMOUNT;
struct HSL color = {0, 1, .5};
bool changeColor = false;
void fadeColor() {
    time_t time = CLOCK_getTime();

    if (time - lastTime < FADE_TIME)
        return;

    lastTime = time;
    
    if(color.H == 360) {
        color.H = 0;
    } else {
        color.H += 1;
    }
    fadeAmmount -= 1;
    if(fadeAmmount == 0) {
        fadeAmmount = FADE_AMMOUNT;
        changeColor = false;
    }
    LED_setHSL(color);
}


void LED_task() {
    if(isDMXOn()) {
        LED_setColor(dmxData[address+1], dmxData[address+2], dmxData[address+3], dmxData[address+4]);
    } else {
        if(BEAT_detected()) {
            changeColor = true;
        }
        if(changeColor) {
            fadeColor();
        }
        
    }
}

