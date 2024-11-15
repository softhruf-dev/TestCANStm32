#include "main.h"
#include "switches.h"
#include <string.h>
#include "uart.h"
#include "system.h"

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

KeyStatus keyStatus;
void initKeyStatus()
{
	memset(&keyStatus, 0, sizeof(KeyStatus));
	keyStatus.lstatus.sw1 = HAL_GPIO_ReadPin(SP_A1_GPIO_Port, SP_A1_Pin);
	keyStatus.lstatus.sw2 = HAL_GPIO_ReadPin(SP_A2_GPIO_Port, SP_A2_Pin);
	keyStatus.rstatus.sw1 = !HAL_GPIO_ReadPin(SP_A1_R_GPIO_Port, SP_A1_R_Pin);
	keyStatus.rstatus.sw2 = !HAL_GPIO_ReadPin(SP_A2_R_GPIO_Port, SP_A2_R_Pin);
	keyStatus.rstatus.sw3 = !HAL_GPIO_ReadPin(SP_A3_GPIO_Port, SP_A3_Pin);
	keyStatus.rstatus.sw4 = !HAL_GPIO_ReadPin(SP_A3_GPIO_Port, SP_A3_Pin);
	keyStatus.rstatus.sw5 = HAL_GPIO_ReadPin(SP_A5_GPIO_Port, SP_A5_Pin);
	keyStatus.rstatus.swt1 = HAL_GPIO_ReadPin(ST_A5_GPIO_Port, ST_A5_Pin);
	keyStatus.lstatus.enc1_sw = HAL_GPIO_ReadPin(E_S1_GPIO_Port, E_S1_Pin);
	keyStatus.lstatus.enc2_sw = HAL_GPIO_ReadPin(E_S2_GPIO_Port, E_S2_Pin);
	keyStatus.lstatus.enc3_sw = HAL_GPIO_ReadPin(E_S3_GPIO_Port, E_S3_Pin);
	keyStatus.lstatus.enc4_sw = HAL_GPIO_ReadPin(E_S4_GPIO_Port, E_S4_Pin);
}
void keyCheck()
{
	uint8_t sw = 0;
	
	//left - sw1 
	sw = HAL_GPIO_ReadPin(SP_A1_GPIO_Port, SP_A1_Pin);
	if(keyStatus.lstatus.sw1 != sw)
	{
		keyStatus.lstatus.sw1 = sw;
		if(sw == SW_ON) {
				flgEvents[EV_L_SW1_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - sw1 turned on \r\n");
#endif
		} else {
			flgEvents[EV_L_SW1_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - sw1 turned off \r\n");
#endif
		}
	}
	
	//left - sw2
	sw = HAL_GPIO_ReadPin(SP_A2_GPIO_Port, SP_A2_Pin);
	if(keyStatus.lstatus.sw2 != sw)
	{
		keyStatus.lstatus.sw2 = sw;
		if(sw == SW_ON) {
			flgEvents[EV_L_SW2_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - sw2 turned on \r\n");
#endif
		} else {
			flgEvents[EV_L_SW2_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - sw2 turned off \r\n");
#endif
		}
	}

	//right - sw1
	sw = HAL_GPIO_ReadPin(SP_A1_R_GPIO_Port, SP_A1_R_Pin);
	if(keyStatus.rstatus.sw1 != !sw)
	{
		keyStatus.rstatus.sw1 = !sw;
		if(keyStatus.rstatus.sw1 == SW_ON) {
			flgEvents[EV_R_SW1_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw1 turned on \r\n");
#endif
		} else {
			flgEvents[EV_R_SW1_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw1 turned off \r\n");
#endif
		}
	}

	//right - sw2
	sw = HAL_GPIO_ReadPin(SP_A2_R_GPIO_Port, SP_A2_R_Pin);
	if(keyStatus.rstatus.sw2 != !sw)
	{
		keyStatus.rstatus.sw2 = !sw;
		if(keyStatus.rstatus.sw2 == SW_ON) {
			flgEvents[EV_R_SW2_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw2 turned on \r\n");
#endif
		} else {
			flgEvents[EV_R_SW2_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw2 turned off \r\n");
#endif
		}
	}

	//right - sw3
	sw = HAL_GPIO_ReadPin(SP_A3_GPIO_Port, SP_A3_Pin);
	if(keyStatus.rstatus.sw3 != !sw)
	{
		keyStatus.rstatus.sw3 = !sw;
		if(keyStatus.rstatus.sw3 == SW_ON) {
			flgEvents[EV_R_SW3_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw3 turned on \r\n");
#endif
		} else {
			flgEvents[EV_R_SW3_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw3 turned off \r\n");
#endif
		}
	}

	//right - sw4
	sw = HAL_GPIO_ReadPin(SP_A4_GPIO_Port, SP_A4_Pin);
	if(keyStatus.rstatus.sw4 != !sw)
	{
		keyStatus.rstatus.sw4 = !sw;
		if(keyStatus.rstatus.sw4 == SW_ON) {
			flgEvents[EV_R_SW4_ON]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw4 turned on \r\n");
#endif
		} else {
			flgEvents[EV_R_SW4_OFF]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw4 turned off \r\n");
#endif
		}
	}

	//right - sp5
	sw = HAL_GPIO_ReadPin(SP_A5_GPIO_Port, SP_A5_Pin);
	if(keyStatus.rstatus.sw5 != sw)
	{
		keyStatus.rstatus.sw5 = sw;
		if(keyStatus.rstatus.sw5 == SW_ON) {
			flgEvents[EV_R_SW5_PRESS]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw5 pressed \r\n");
#endif
		} else {
			flgEvents[EV_R_SW5_RELEASE]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - sw5 released \r\n");
#endif
		}
	}

	//right - swt1 (tactile)
	sw = HAL_GPIO_ReadPin(ST_A5_GPIO_Port, ST_A5_Pin);
	if(keyStatus.rstatus.swt1 != sw)
	{
		keyStatus.rstatus.swt1 = sw;
		if(keyStatus.rstatus.swt1 == SW_ON) {
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - tactile pressed \r\n");
#endif
		} else {
			flgEvents[EV_R_TACTILE_CLICKED]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "right - tactile released \r\n");
#endif
		}
	}

	//left - enc1
	uint8_t _a, _b;
	static uint8_t _enc1_ab = 0;

	sw = HAL_GPIO_ReadPin(E_S1_GPIO_Port, E_S1_Pin);
	if(keyStatus.lstatus.enc1_sw != sw)
	{
		keyStatus.lstatus.enc1_sw = sw;
		if(keyStatus.lstatus.enc1_sw == SW_ON) {
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc1 clicked \r\n");
#endif
		} else {
			flgEvents[EV_L_ENC1_CLICKED]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc1 released \r\n");
#endif
		}
	}
	
	_a = HAL_GPIO_ReadPin(E_A1_GPIO_Port, E_A1_Pin);
	_b = HAL_GPIO_ReadPin(E_B1_GPIO_Port, E_B1_Pin);
	
	if( (_enc1_ab & 3) != (_a << 1) + _b )
	{
		if(_a == 1 && _b == 1){
			if(_enc1_ab == 0x12)
			{
				keyStatus.lstatus.enc1++;
				flgEvents[EV_L_ENC1_INC]++;

		#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc1 increase %d\r\n", keyStatus.lstatus.enc1);
		#endif
			} else if(_enc1_ab == 0x21)
			{
				keyStatus.lstatus.enc1--;
				flgEvents[EV_L_ENC1_DEC]++;
				#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc1 decrease %d\r\n", keyStatus.lstatus.enc1);
				#endif
			}
			_enc1_ab = 0;
		}
		else {
			_enc1_ab = (_enc1_ab << 2) + (_a << 1) + _b;
		}
	}
	
	//left - enc2
	static uint8_t _enc2_ab = 0;
	sw = HAL_GPIO_ReadPin(E_S2_GPIO_Port, E_S2_Pin);
	if(keyStatus.lstatus.enc2_sw != sw)
	{
		keyStatus.lstatus.enc2_sw = sw;
		if(keyStatus.lstatus.enc2_sw == SW_ON) {
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc2 clicked \r\n");
#endif
		} else {
			flgEvents[EV_L_ENC2_CLICKED] = 1;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc2 released \r\n");
#endif
		}
	}
	
	_a = HAL_GPIO_ReadPin(E_A2_GPIO_Port, E_A2_Pin);
	_b = HAL_GPIO_ReadPin(E_B2_GPIO_Port, E_B2_Pin);
	
	if( (_enc2_ab & 3) != (_a << 1) + _b )
	{
		if(_a == 1 && _b == 1){
			if(_enc2_ab == 0x12)
			{
				keyStatus.lstatus.enc2++;
				flgEvents[EV_L_ENC2_INC]++;
		#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc2 increase %d\r\n", keyStatus.lstatus.enc2);
		#endif
			} else if(_enc2_ab == 0x21)
			{
				flgEvents[EV_L_ENC2_DEC]++;
				keyStatus.lstatus.enc2--;
				#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc2 decrease %d\r\n", keyStatus.lstatus.enc2);
				#endif
			}
			_enc2_ab = 0;
		}
		else {
			_enc2_ab = (_enc2_ab << 2) + (_a << 1) + _b;
		}
	}
	
	//left - enc3
	static uint8_t _enc3_ab = 0;
	sw = HAL_GPIO_ReadPin(E_S3_GPIO_Port, E_S3_Pin);
	if(keyStatus.lstatus.enc3_sw != sw)
	{
		keyStatus.lstatus.enc3_sw = sw;
		if(keyStatus.lstatus.enc3_sw == SW_ON) {
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc3 clicked \r\n");
#endif
		} else {
			flgEvents[EV_L_ENC3_CLICKED]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc3 released \r\n");
#endif
		}
	}
	
	_a = HAL_GPIO_ReadPin(E_A3_GPIO_Port, E_A3_Pin);
	_b = HAL_GPIO_ReadPin(E_B3_GPIO_Port, E_B3_Pin);
	
	if( (_enc3_ab & 3) != (_a << 1) + _b )
	{
		if(_a == 1 && _b == 1){
			if(_enc3_ab == 0x12)
			{
				keyStatus.lstatus.enc3++;
				flgEvents[EV_L_ENC3_INC]++;
		#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc3 increase %d\r\n", keyStatus.lstatus.enc3);
		#endif
			} else if(_enc3_ab == 0x21)
			{
				keyStatus.lstatus.enc3--;
				flgEvents[EV_L_ENC3_DEC]++;
				#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc3 decrease %d\r\n", keyStatus.lstatus.enc3);
				#endif
			}
			_enc3_ab = 0;
		}
		else {
			_enc3_ab = (_enc3_ab << 2) + (_a << 1) + _b;
		}
	}
	
	//left - enc4
	static uint8_t _enc4_ab = 0;
	sw = HAL_GPIO_ReadPin(E_S4_GPIO_Port, E_S4_Pin);
	if(keyStatus.lstatus.enc4_sw != sw)
	{
		keyStatus.lstatus.enc4_sw = sw;
		if(keyStatus.lstatus.enc4_sw == SW_ON) {
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc4 clicked \r\n");
#endif
		} else {
			flgEvents[EV_L_ENC4_CLICKED]++;
#if defined(RTT_SEGGER_DEBUGER)
			SEGGER_RTT_printf(0, "left - enc4 released \r\n");
#endif
		}
	}
	
	_a = HAL_GPIO_ReadPin(E_A4_GPIO_Port, E_A4_Pin);
	_b = HAL_GPIO_ReadPin(E_B4_GPIO_Port, E_B4_Pin);
	
	if( (_enc4_ab & 3) != (_a << 1) + _b )
	{
		if(_a == 1 && _b == 1){
			if(_enc4_ab == 0x12)
			{
				keyStatus.lstatus.enc4++;
				flgEvents[EV_L_ENC4_INC]++;

		#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc4 increase %d\r\n", keyStatus.lstatus.enc4);
		#endif
			} else if(_enc4_ab == 0x21)
			{
				keyStatus.lstatus.enc4--;
				flgEvents[EV_L_ENC4_DEC]++;

				#if defined(RTT_SEGGER_DEBUGER)
					SEGGER_RTT_printf(0, "left - enc4 decrease %d\r\n", keyStatus.lstatus.enc4);
				#endif
			}
			_enc4_ab = 0;
		}
		else {
			_enc4_ab = (_enc4_ab << 2) + (_a << 1) + _b;
		}
	}
	
}
