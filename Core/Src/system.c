#include <string.h>
#include "main.h"
#include "system.h"
#include "uart.h"
#include "switches.h"
#include "ws2812.h"
#include "joystick.h"
#include "can.h"

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

uint8_t g_nBrightness = 10;

uint8_t flgEvents[EV_CNT] = {0};
uint8_t flgUsrEvents[USR_CMD_CNT] = {0};

void initApp()
{
	initKeyStatus();
	keyCheck();
	memset(flgEvents, 0, sizeof(flgEvents));
	initLEDs();
	initAdc();
	
	kbTest();
}

void appHandler()
{
	uartPacketRcvProc();
	usrEventHandler();
	keyCheck();
	keyboardCheck();
	eventHandler();
	ledHandler();
	joystickHandler();
}

void eventHandler()
{
	uint8_t i = 0;
	uint8_t sbuf[2];
	memset((void *) sbuf, 0, 2);
	
	for(i = 0; i < EV_CNT; i++)
	{
		if(flgEvents[i] > 0) {
			switch(i) {
				case EV_L_SW1_ON:
					break;
				case EV_L_SW1_OFF:
					break;
				case EV_L_SW2_ON:
					break;
				case EV_L_SW2_OFF:
					break;
				case EV_R_SW1_ON:
					break;
				case EV_R_SW1_OFF:
					break;
				case EV_R_SW2_ON:
					break;
				case EV_R_SW2_OFF:
					break;
				case EV_R_SW3_ON:
					break;
				case EV_R_SW3_OFF:
					break;
				case EV_R_SW4_ON:
					break;
				case EV_R_SW4_OFF:
					break;
				case EV_R_SW5_PRESS:
					break;
				case EV_R_SW5_RELEASE:
					break;
				case EV_R_TACTILE_CLICKED:
					break;
				case EV_L_ENC1_CLICKED:
					break;
				case EV_L_ENC1_INC:
					break;
				case EV_L_ENC1_DEC:
					break;
				case EV_L_ENC2_CLICKED:
					break;
				case EV_L_ENC2_INC:
					break;
				case EV_L_ENC2_DEC:
					break;
				case EV_L_ENC3_CLICKED:
					break;
				case EV_L_ENC3_INC:
					break;
				case EV_L_ENC3_DEC:
					break;
				case EV_L_ENC4_CLICKED:
					break;
				case EV_L_ENC4_INC:
					break;
				case EV_L_ENC4_DEC:				
					break;
				case JS_L_X_INC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left x inc\r\n");
	#endif
					break;
				case JS_L_X_DEC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left x dec\r\n");
	#endif
					break;
				case JS_L_X_FREE:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left x free\r\n");
	#endif
					break;
				case JS_L_Y_INC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left y inc\r\n");
	#endif
					break;
				case JS_L_Y_DEC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left y dec\r\n");
	#endif
					break;
				case JS_L_Y_FREE:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick left y free\r\n");
	#endif
					break;
				case JS_R_X_INC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right x inc\r\n");
	#endif
					break;
				case JS_R_X_DEC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right x dec\r\n");
	#endif
					break;
				case JS_R_X_FREE:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right x free\r\n");
	#endif
					break;
				case JS_R_Y_INC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right y inc\r\n");
	#endif
					break;
				case JS_R_Y_DEC:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right y dec\r\n");
	#endif
					break;
				case JS_R_Y_FREE:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "joystick right y free\r\n");
	#endif
					break;
				case EV_PT_K1_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 1 click on\r\n");
	#endif
					break;
				case EV_PT_K1_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 1 click on\r\n");
	#endif
					break;
				case EV_PT_K2_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 2 click on\r\n");
	#endif
					break;
				case EV_PT_K2_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 2 click off\r\n");
	#endif
					break;
				case EV_PT_K3_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 3 click on\r\n");
	#endif
					break;
				case EV_PT_K3_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 3 click off\r\n");
	#endif
					break;
				case EV_PT_K4_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 4 click on\r\n");
	#endif
					break;
				case EV_PT_K4_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 4 click off\r\n");
	#endif
					break;
				case EV_PT_K5_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 5 click on\r\n");
	#endif
					break;
				case EV_PT_K5_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 5 click off\r\n");
	#endif
					break;
				case EV_PT_K6_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 6 click on\r\n");
	#endif
					break;
				case EV_PT_K6_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 6 click off\r\n");
	#endif
					break;
				case EV_PT_K7_ON:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 7 click on\r\n");
	#endif
					break;
				case EV_PT_K7_OFF:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard 7 click off\r\n");
	#endif
					break;
				case EV_PT_ENC_CW:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard encoder increased\r\n");
	#endif
					break;
				case EV_PT_ENC_CCW:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "keyboard encoder decreased\r\n");
	#endif
					break;
			}
			sbuf[0] = USR_CMD_KEYCODE;
			sbuf[1] = i+'a';

			UartPacketSend(sbuf, 2);
			flgEvents[i] = 0;
		}
	}
}

void usrEventHandler()
{
	uint8_t i = 0;
	uint8_t sbuf[16];
	uint8_t packLen = 5;
	memset((void *) sbuf, 0, 16);
	
	for(i = 0; i < USR_CMD_CNT; i++)
	{
		if(flgUsrEvents[i] > 0) {
			switch(i) {
				case USR_CMD_VERSION:
	#if defined(RTT_SEGGER_DEBUGER)
		SEGGER_RTT_printf(0, "read version command\r\n");
	#endif	
					sbuf[0] = USR_CMD_VERSION;
					sbuf[1] = '0'+MAJOR;
					sbuf[2] = '.';
					sbuf[3] = '0'+MINOR;
					UartPacketSend(sbuf, 4);
					break;
			}		

			flgUsrEvents[i] = 0;
		}
	}
}

void ledHandler()
{
	static uint16_t draw_cnt = 0;
	uint8_t i = 0;
	
	if(draw_cnt++ > 1000) {
		/* @ref
		//use LED control function
		setAllLEDBrightness(0);
		setLEDColor(mainColor, i);
		setLEDColor(backColor, i);
		setAllLEDBrightness(2);
		*/
		for(i = 0; i < NUM_LEDS; i++)
		{
			setLEDColor(mainColor, i);
		}
		setAllLEDBrightness(g_nBrightness);
		drawLEDs();
		draw_cnt = 0;
	}
//	HAL_Delay(100);
}

void joystickHandler()
{
	adcHandler();
	if(joystick.l_x < joystickStatus.l_x_min) {
		if(joystickStatus.l_x_event != 1)
			flgEvents[JS_L_X_INC] = 1;
		joystickStatus.l_x_event = 1;
	}
	else if(joystick.l_x > joystickStatus.l_x_max) {
		if(joystickStatus.l_x_event != 2)
			flgEvents[JS_L_X_DEC] = 1;
		joystickStatus.l_x_event = 2;
	}
	else {
		if(joystickStatus.l_x_event != 0)
			flgEvents[JS_L_X_FREE] = 1;
		joystickStatus.l_x_event = 0;
	}
	
	//l_y
	if(joystick.l_y < joystickStatus.l_y_min) {
		if(joystickStatus.l_y_event != 1)
			flgEvents[JS_L_Y_INC] = 1;
		joystickStatus.l_y_event = 1;
	}
	else if(joystick.l_y > joystickStatus.l_y_max) {
		if(joystickStatus.l_y_event != 2)
			flgEvents[JS_L_Y_DEC] = 1;
		joystickStatus.l_y_event = 2;
	}
	else {
		if(joystickStatus.l_y_event != 0)
			flgEvents[JS_L_Y_FREE] = 1;
		joystickStatus.l_y_event = 0;
	}
	
	//r_x
	if(joystick.r_x < joystickStatus.r_x_min) {
		if(joystickStatus.r_x_event != 1)
			flgEvents[JS_R_X_INC] = 1;
		joystickStatus.r_x_event = 1;
	}
	else if(joystick.r_x > joystickStatus.r_x_max) {
		if(joystickStatus.r_x_event != 2)
			flgEvents[JS_R_X_DEC] = 1;
		joystickStatus.r_x_event = 2;
	}
	else {
		if(joystickStatus.r_x_event != 0)
			flgEvents[JS_R_X_FREE] = 1;
		joystickStatus.r_x_event = 0;
	}
	
	//r_y
	if(joystick.r_y < joystickStatus.r_y_min) {
		if(joystickStatus.r_y_event != 1)
			flgEvents[JS_R_Y_INC] = 1;
		joystickStatus.r_y_event = 1;
	}
	else if(joystick.r_y > joystickStatus.r_y_max) {
		if(joystickStatus.r_y_event != 2)
			flgEvents[JS_R_Y_DEC] = 1;
		joystickStatus.r_y_event = 2;
	}
	else {
		if(joystickStatus.r_y_event != 0)
			flgEvents[JS_R_Y_FREE] = 1;
		joystickStatus.r_y_event = 0;
	}
}


void process_packet(uint8_t* payload, uint8_t len);
void uartPacketRcvProc(void) 
{
	if(flg_packetReceived) {
		process_packet(&rx_buffer[2], rx_buffer[1]);
		flg_packetReceived = 0;
	}
}

void process_packet(uint8_t* payload, uint8_t len)
{
	if(payload[0] == 'R')
	{
		NVIC_SystemReset();
	} else if(payload[0] == 'V' && payload[1] == 'E' && payload[2] == 'R' && payload[3] == 'S') {
		flgUsrEvents[USR_CMD_VERSION]++;
	} else if(payload[0] == 'C') {
		switch(payload[1])
		{
			case USR_CMD_C_BRIGHTNESS:
				g_nBrightness = payload[2];				
				break;
		}
	}
}