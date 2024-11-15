#include "main.h"
#include "joystick.h"
#include <string.h>

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

Joystick joystick;
JoystickStatus joystickStatus;
uint16_t adcBuf[CH_CNT*ADC_BUFSIZE];
uint8_t curCh;
uint8_t flgAdcCompleted = 1;

void initAdc()
{
	curCh = CH_LEFT_X;
	memset(adcBuf, 0, sizeof(uint16_t)*CH_CNT*ADC_BUFSIZE);
	joystickStatus.l_x_min = 1800;
	joystickStatus.l_x_max = 2200;
	joystickStatus.l_y_min = 1810;
	joystickStatus.l_y_max = 2210;
	joystickStatus.r_x_min = 1820;
	joystickStatus.r_x_max = 2320;
	joystickStatus.r_y_min = 1800;
	joystickStatus.r_y_max = 2200;
}

uint8_t startAdc(uint8_t nCh)
{
	uint8_t nRet = 0;
	ADC_ChannelConfTypeDef sConfig = {0};
  /** Configure Regular Channel
  */
	if(nCh == CH_LEFT_X)
			nCh = ADC_CHANNEL_8;
	if(nCh == CH_LEFT_Y)
			nCh = ADC_CHANNEL_11;
	else if(nCh == CH_RIGHT_X)
			nCh = ADC_CHANNEL_10;
	else if(nCh == CH_RIGHT_Y)
			nCh = ADC_CHANNEL_9;
	else
		nCh = ADC_CHANNEL_8;

  sConfig.Channel = nCh;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
		nRet = 1;
  }
	flgAdcCompleted = 0;
	HAL_ADC_Start_IT(&hadc1);
	return nRet;
}

uint8_t readyAdc()
{
	uint8_t nRet = 0;
	if(flgAdcCompleted)
		nRet = 1;
	
	
	return nRet;
}
uint16_t readAdc(uint8_t nCh)
{
	uint16_t nResult;
	if(nCh < CH_CNT)
		nResult = adcBuf[(ADC_BUFSIZE - 1)*CH_CNT + nCh];
	else
		nResult = adcBuf[(curCh/CH_CNT - 1)*CH_CNT + nCh];
	
	return nResult;
}

void readAdcCallback(uint16_t adval)
{
	adcBuf[curCh] = adval;
	flgAdcCompleted = 1;
}

void adcHandler()
{
	static uint8_t chCnt = 0;
	static uint8_t bufCnt = 0;
	static uint32_t cnt = 0;
	static uint32_t tm = 0;
	
	if(cnt ++ > 500) {
		if(readyAdc())
		{
			startAdc(chCnt);
			chCnt++;
			if(chCnt >= CH_CNT) {
				chCnt = 0;
				bufCnt++;
				if(bufCnt >= ADC_BUFSIZE)
					bufCnt = 0;
			}
			curCh = bufCnt*CH_CNT + chCnt;
		}

		joystick.l_x = readAdc(CH_LEFT_X);
		joystick.l_y = readAdc(CH_LEFT_Y);
		joystick.r_x = readAdc(CH_RIGHT_X);
		joystick.r_y = readAdc(CH_RIGHT_Y);
	#if defined(RTT_SEGGER_DEBUGER)
		
		//SEGGER_RTT_printf(0, "joystick:[%d, %d],[%d, %d]\r\n", joystick.l_x, joystick.l_y, joystick.r_x, joystick.r_y);
	#endif
		cnt = 0;
	}
}




