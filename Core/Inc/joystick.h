/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define ADC_BUFSIZE		2
#define CH_CNT				4

typedef enum ENM_JOYSTICK_CHANNEL {
	CH_LEFT_X = 0,
	CH_LEFT_Y,
	CH_RIGHT_X,
	CH_RIGHT_Y
} JOYSTICK_CHANNEL;

typedef struct _Joystick {
	uint32_t l_x;
	uint32_t l_y;
	uint32_t r_x;
	uint32_t r_y;
} Joystick;

typedef struct _JoystickStatus {
	
	uint32_t l_x_min;
	uint32_t l_x_max;

	uint32_t l_y_min;
	uint32_t l_y_max;

	uint32_t r_x_min;
	uint32_t r_x_max;

	uint32_t r_y_min;
	uint32_t r_y_max;
	
	uint8_t	l_x_event;
	uint8_t	l_y_event;
	uint8_t	r_x_event;
	uint8_t	r_y_event;

} JoystickStatus;

extern Joystick joystick;
extern JoystickStatus joystickStatus;
extern uint16_t adcBuf[CH_CNT*ADC_BUFSIZE];
extern uint8_t curCh;
extern ADC_HandleTypeDef hadc1;
extern uint8_t flgAdcCompleted;

void initAdc(void);
uint8_t startAdc(uint8_t nCh);
uint16_t readAdc(uint8_t nCh);
uint8_t readyAdc(void);
void adcHandler(void);
void readAdcCallback(uint16_t adval);
#ifdef __cplusplus
}
#endif
#endif /*__JOYSTICK_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
