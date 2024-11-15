/*
	CAN driver for Power track
	- J1939 protocol
	- baud rate 250k
	- background led on/off, change color	
	- receive the events
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

void canInit(void);
void keyboardCheck(void);
void kbTest(void);

#ifdef __cplusplus
}
#endif
#endif /*__CAN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
