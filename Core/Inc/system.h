/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
enum ENM_EVENTCODE {
	EV_L_SW1_ON,
	EV_L_SW1_OFF,
	EV_L_SW2_ON,
	EV_L_SW2_OFF,
	EV_R_SW1_ON,
	EV_R_SW1_OFF,
	EV_R_SW2_ON,
	EV_R_SW2_OFF,
	EV_R_SW3_ON,
	EV_R_SW3_OFF,
	EV_R_SW4_ON,
	EV_R_SW4_OFF,
	EV_R_SW5_PRESS,
	EV_R_SW5_RELEASE,
	EV_R_TACTILE_CLICKED,
	EV_L_ENC1_CLICKED,
	EV_L_ENC1_INC,
	EV_L_ENC1_DEC,
	EV_L_ENC2_CLICKED,
	EV_L_ENC2_INC,
	EV_L_ENC2_DEC,
	EV_L_ENC3_CLICKED,
	EV_L_ENC3_INC,
	EV_L_ENC3_DEC,
	EV_L_ENC4_CLICKED,
	EV_L_ENC4_INC,
	EV_L_ENC4_DEC,
	JS_L_X_INC,
	JS_L_X_DEC,
	JS_L_X_FREE,
	JS_L_Y_INC,
	JS_L_Y_DEC,
	JS_L_Y_FREE,
	JS_R_X_INC,
	JS_R_X_DEC,
	JS_R_X_FREE,
	JS_R_Y_INC,
	JS_R_Y_DEC,
	JS_R_Y_FREE,
	
	//power track
	EV_PT_K1_ON,
	EV_PT_K1_OFF,
	EV_PT_K2_ON,
	EV_PT_K2_OFF,
	EV_PT_K3_ON,
	EV_PT_K3_OFF,
	EV_PT_K4_ON,
	EV_PT_K4_OFF,
	EV_PT_K5_ON,
	EV_PT_K5_OFF,
	EV_PT_K6_ON,
	EV_PT_K6_OFF,
	EV_PT_K7_ON,
	EV_PT_K7_OFF,
	EV_PT_ENC_CW,
	EV_PT_ENC_CCW,
	
	EV_CNT
};

enum ENM_EV_USR_CODE {
	//user defined
	USR_CMD_NONE,
	USR_CMD_KEYCODE,
	USR_CMD_RESET,
	USR_CMD_VERSION,
	USR_CMD_C_BRIGHTNESS,
	
	USR_CMD_CNT
};



extern uint8_t flgEvents[EV_CNT];
extern uint8_t flgUsrEvents[USR_CMD_CNT];

void initApp(void);
void appHandler(void);
void eventHandler(void);	 
void ledHandler(void);
void joystickHandler(void);
void uartPacketRcvProc(void);
void usrEventHandler(void);

extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
#ifdef __cplusplus
}
#endif
#endif /*__SYSTEM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
