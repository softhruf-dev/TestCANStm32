#include "main.h"
#include "myfile.h"
#include <string.h>

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

void delay_us(uint16_t us)
{
	uint16_t i;
	__IO uint16_t j;
	for(i=0;i<us;i++)
		for(j=0;j<65;j++);
}

void Test_Gpio()
{
	//led1 blinking
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
#if defined(RTT_SEGGER_DEBUGER)
	SEGGER_RTT_WriteString(0, "Toggle LED pin \r\n");
#endif
	HAL_Delay(1000);
}

uint8_t LED_Data[NUM_LED][4];

void setLED(int led, int RED, int GREEN, int BLUE)
{
	LED_Data[led][0] = led;
	LED_Data[led][1] = GREEN;
	LED_Data[led][2] = RED;
	LED_Data[led][3] = BLUE;
}

void ws2812_spi(int RED, int GREEN, int BLUE)
{
	uint32_t color = GREEN << 16 | RED <<8 | BLUE;
	uint8_t sendData[24];
	int indx = 0;
	for (int i = 23; i >= 0; i--)
	{
		if(((color>>i)&0x01) == 1)
			sendData[indx++] = 6; //store 1 (0b110)
		else 
			sendData[indx++] = 4; //store 0 (0b100)
	}
//	HAL_SPI_Transmit(&hspi2, sendData, 24, 1000);
	
}

void WS2812_Send()
{
	for(int i = 0; i < NUM_LED; i++)
	{
		ws2812_spi(LED_Data[i][1], LED_Data[i][2], LED_Data[i][3]);
	}
}

void Test_WS2812B()
{
   for (int i=0; i<NUM_LED; i++)
	{
		setLED(i, 255, 0, 0);
	}
	WS2812_Send();
	HAL_Delay(1000);
   for (int i=0; i<NUM_LED; i++)
	{
		setLED(i, 0, 255, 0);
	}
	WS2812_Send();
	HAL_Delay(1000);
   for (int i=0; i<NUM_LED; i++)
	{
		setLED(i, 0, 0, 255);
	}
	WS2812_Send();
	HAL_Delay(1000);
}


