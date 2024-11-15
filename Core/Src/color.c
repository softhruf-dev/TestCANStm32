#include "ws2812.h"
#include <stdio.h>
#include "main.h"
#include <stdbool.h>
#include <string.h>

#pragma pack(1)

static RGB pixels[NUM_LEDS];

static void calcPixelColor(uint32_t src, uint8_t* out)
{
	uint8_t offset = 0;
	uint16_t buf = 0;
	uint8_t *pPData = (uint8_t*)out;
	uint32_t cData  = src;	
	for(uint8_t i = 0; i < 24; i++)
	{
		buf <<= 4; offset += 4;
		if(cData & 0x800000) buf |= BIT_ON; else buf |= BIT_OFF;
		if(offset >= 8)
		{
			offset -= 8;
			*pPData = (buf >> offset) & 0xFF; 
			buf = 0;
			pPData++;
		}
	/*	if(offset >= 8)
		{
			offset -= 8;

			buf &= mask[offset]; 
			
		}		
		*/
		cData <<= 1;
	}
}



void calcsPixelsColor(ONEPIXEL *pixelData)
{
	uint32_t colBuf = 0;	
	memset(pixelData,0, sizeof(ONEPIXEL) * (NUM_LEDS + 2));
	for(uint8_t i = 0; i < NUM_LEDS; i++)
	{
		colBuf = (pixels[i].G << 16) + (pixels[i].R << 8) + (pixels[i].B );
		calcPixelColor(colBuf,  (uint8_t*)&pixelData[i]);
	}
}

void setLEDColor(RGB color, uint8_t pos)
{
	pixels[pos] = color;
}

void setLEDColorBight(RGB color, int8_t pos, uint8_t bright)
{
	if(pos < 0) return;
	pixels[pos].R = color.R * 1.0f * bright / 100;
	pixels[pos].G = color.G * 1.0f * bright / 100;
	pixels[pos].B = color.B * 1.0f * bright / 100;
	
}

void setAllLEDColor(RGB color)
{
	for(uint8_t i = 0; i < NUM_LEDS; i++) pixels[i] = color;
}

void brighnessChange(RGB* color, uint8_t scale)
{
		color->R = color->R * 1.0f * scale / 100;
		color->G = color->G * 1.0f * scale / 100;
		color->B = color->B * 1.0f * scale / 100;	
}

void setAllLEDBrightness(uint8_t scale)
{
	for(uint8_t i = 0; i < NUM_LEDS; i++) brighnessChange(&pixels[i], scale);
}


void calculateBreath(RGB* col, uint16_t cnt, uint16_t period)
{
	uint8_t R,G,B;
	float k = 0.0f;
	R = col->R; G = col->G; B = col->B; 

	if(period > cnt) k = (period - cnt) * 1.0f / period * 1.0f;
	else  k = (cnt - period) * 1.0f / period ;
	if(k < 0.05f) k = 0.05f;
	R = (uint8_t)(R * 1.0f* k);
	G = (uint8_t)(G * 1.0f* k);
	B = (uint8_t)(B * 1.0f* k);
	
	col->R = R;
	col->G = G;
	col->B = B;
	
}

void calculateFlash(RGB* color, uint16_t cnt, uint16_t period)
{
	if(cnt < period) return;
	color->R = 0;
	color->G = 0;
	color->B = 0;
}

void calculateRainbowbreathing(RGB* color, uint16_t cnt, uint16_t period)
{
	
	uint16_t hue = 0;
	hue = (uint16_t)(cnt * 360 * 1.0f / period);
	uint8_t hueBuf = hue % 60;
	float hueoffset = hueBuf * 4.25f;
	if(hueoffset > 255.0f) hueoffset = 255.0f;
			 if(hue < 60) 	{		color->R = 255; 								  color->G = hueoffset; 								color->B = 0;	}
	else if(hue < 120) 	{		color->R = (255 - hueoffset); 		color->G = 255; 											color->B = 0;	}
	else if(hue < 180) 	{		color->R = 0; 										color->G = 255; 											color->B = hueoffset;	}
	else if(hue < 240) 	{		color->R = 0; 										color->G = (255 - hueoffset); 				color->B = 255;	}
	else if(hue < 300) 	{		color->R = hueoffset; 						color->G = 0; 												color->B = 255;	}
	else if(hue < 360) 	{		color->R = 255; 									color->G = 0; 												color->B = (255 - hueoffset);	}
}


