#ifndef __WS2812_H
#define __WS2812_H

#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"

#define NUM_LEDS	8*4
#define LED_SCANNING_PERIOD 1
#define LED_MAX_BRIGHTNESS	10

#define BIT_ON			0xE
#define BIT_OFF			0x8

#define COLOR_CHANGED	0
#define MODE_CHANGED	1

typedef struct _RGB{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB;

typedef struct _CHSV{
	uint8_t hue;
	uint8_t sat;
	uint8_t val;
}CHSV;


typedef struct _ONEPIXEL{
	uint8_t dt[12];
}ONEPIXEL;


typedef struct PIXEL_PROPERTY_
{
	RGB 						color;
	uint8_t 				scale;
	uint8_t 				maxBirghtnes;
	RGB							prvColor;
	uint16_t 				cnt;
}PIXEL_PROPERTY;

void calcsPixelsColor(ONEPIXEL *pixelData);

void setLEDColor(RGB color, uint8_t pos);
void setAllLEDColor(RGB color);
void setLEDColorBight(RGB color, int8_t pos, uint8_t bright);
void setAllLEDBrightness(uint8_t scale);

void updateLEDScanning(void);
void updateLEDFlashing(void);
void setColor(RGB _mainColor, RGB _backColor);
void drawLEDs(void);
void initLEDs(void);

void calculateBreath(RGB* color, uint16_t cnt, uint16_t period);
void calculateFlash(RGB* color, uint16_t cnt, uint16_t period);
void calculateRainbowbreathing(RGB* color, uint16_t cnt, uint16_t period);



void updateColorMode(void);
void updateFlashingMode(void);
void powerOffGlowing(void);
void updateBrightness(void);

extern RGB mainColor;
extern RGB backColor;

extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi2;
#endif




