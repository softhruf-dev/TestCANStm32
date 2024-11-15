/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SWITCHES_H__
#define __SWITCHES_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

typedef struct 
{
	uint16_t 	enc1;
	uint8_t		enc1_sw;
	uint16_t 	enc2;
	uint8_t		enc2_sw;
	uint16_t 	enc3;
	uint8_t		enc3_sw;
	uint16_t 	enc4;
	uint8_t		enc4_sw;
	uint8_t		sw1;
	uint8_t		sw2;
	
	uint8_t		enc1_led[24];
	uint8_t		enc2_led[24];
	uint8_t		enc3_led[24];
	uint8_t		enc4_led[24];

} LStatus;

typedef struct 
{
	uint8_t 	sw1;
	uint8_t 	sw2;
	uint8_t		sw3;
	uint8_t		sw4;
	
	uint8_t 	sw5;
	
	uint8_t		swt1;
	uint8_t 	btn1;
	uint8_t 	btn1_led[24];
} RStatus;

typedef struct 
{
	LStatus lstatus;
	RStatus	rstatus;
} KeyStatus;

enum SW_STATUS {
	SW_ON,
	SW_OFF
};

extern KeyStatus keyStatus;

void keyCheck(void);
void initKeyStatus(void);
	
#ifdef __cplusplus
}
#endif
#endif /*__SWITCHES_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
