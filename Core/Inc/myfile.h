/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_FILE_H__
#define __MY_FILE_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Test_Gpio(void);
#define NUM_LED 1

void setLED(int led, int RED, int GREEN, int BLUE);
void Test_WS2812B (void);

#ifdef __cplusplus
}
#endif
#endif /*__MY_FILE_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
