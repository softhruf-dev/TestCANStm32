#include "ws2812.h"

static PIXEL_PROPERTY pixelProp;
static ONEPIXEL  pixData[NUM_LEDS + 2] = {0};
RGB mainColor = {0, 0, 255};
RGB backColor = {255, 0, 0};

void setColor(RGB _mainColor, RGB _backColor)
{
	mainColor = _mainColor;
	backColor = _backColor;
}
void updateLEDScanning()
{
	static int8_t scanPos = 0;
	
	if(pixelProp.cnt ++ < LED_SCANNING_PERIOD) return;
	pixelProp.cnt = 0;
	
	RGB color = {0,0,0};
	setAllLEDColor(color);
	uint8_t temp1, temp2, temp3, temp4, temp5;
	switch(scanPos)
	{
		case 0: temp1 = 0; temp2 = 39; temp3 = 38;  temp4 = 37; temp5 = 36; break;
		case 1: temp1 = 1; temp2 = 0; temp3 = 39;  temp4 = 38; temp5 = 37; break;
		case 2: temp1 = 2; temp2 = 1; temp3 = 0;  temp4 = 39; temp5 = 38; break;
		case 3: temp1 = 3; temp2 = 2; temp3 = 1;  temp4 = 0; temp5 = 39; break;
		case 4: temp1 = 4; temp2 = 3; temp3 = 2;  temp4 = 1; temp5 = 0; break;
		default: temp1 = scanPos; temp2 = scanPos -1; temp3 = scanPos -2; temp4 = scanPos -3; temp5 = scanPos -4;break;
		
		
	}
	setLEDColorBight(mainColor, temp1, 100);
	
	setLEDColorBight(mainColor, temp2, 80);
	setLEDColorBight(mainColor, temp3, 60);
	setLEDColorBight(mainColor, temp4, 40);	
	setLEDColorBight(mainColor, temp5, 20);	

	scanPos++;
	if(scanPos >= NUM_LEDS) scanPos = 0;
}

void updateLEDFlashing()
{
	static uint8_t scanPos = 0;
	
	RGB color = {255,0,0};
	if(scanPos %10 == 0)
		color = backColor;
	setAllLEDColor(color);
	scanPos++;

}

void drawLEDs(void)
{
	calcsPixelsColor(pixData);
	HAL_SPI_Transmit_DMA(&hspi3, (uint8_t*)pixData, sizeof(pixData));
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*)pixData, sizeof(pixData));
}

void initLEDs(void)
{
	pixelProp.color.R = 0;		pixelProp.color.G = 0;		pixelProp.color.B = 255;
	pixelProp.prvColor = pixelProp.color;
	pixelProp.cnt = 0;
	pixelProp.maxBirghtnes = LED_MAX_BRIGHTNESS;
	
	//turn on leds
	HAL_GPIO_WritePin(LED_ON_GPIO_Port, LED_ON_Pin, GPIO_PIN_SET);
	
		int i;
//	updateLEDFlashing();
	RGB red = {255,0,0};
	RGB green = {0,255,0};
	RGB blue = {0,0,255};
	setAllLEDBrightness(255);
	setAllLEDColor(green);
}

