/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define MAJOR 0
#define MINOR 7

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SP_A3_Pin GPIO_PIN_1
#define SP_A3_GPIO_Port GPIOA
#define SP_B3_Pin GPIO_PIN_4
#define SP_B3_GPIO_Port GPIOA
#define SP_A4_Pin GPIO_PIN_5
#define SP_A4_GPIO_Port GPIOA
#define SP_B4_Pin GPIO_PIN_6
#define SP_B4_GPIO_Port GPIOA
#define CAN_EN_Pin GPIO_PIN_7
#define CAN_EN_GPIO_Port GPIOA
#define E_B4_Pin GPIO_PIN_4
#define E_B4_GPIO_Port GPIOC
#define E_A4_Pin GPIO_PIN_5
#define E_A4_GPIO_Port GPIOC
#define LED_ON_Pin GPIO_PIN_2
#define LED_ON_GPIO_Port GPIOB
#define E_S4_Pin GPIO_PIN_10
#define E_S4_GPIO_Port GPIOB
#define E_B3_Pin GPIO_PIN_11
#define E_B3_GPIO_Port GPIOB
#define E_A3_Pin GPIO_PIN_12
#define E_A3_GPIO_Port GPIOB
#define E_S3_Pin GPIO_PIN_14
#define E_S3_GPIO_Port GPIOB
#define SP_B1_Pin GPIO_PIN_6
#define SP_B1_GPIO_Port GPIOC
#define SP_A1_Pin GPIO_PIN_7
#define SP_A1_GPIO_Port GPIOC
#define E_B2_Pin GPIO_PIN_8
#define E_B2_GPIO_Port GPIOC
#define E_A2_Pin GPIO_PIN_9
#define E_A2_GPIO_Port GPIOC
#define E_S2_Pin GPIO_PIN_8
#define E_S2_GPIO_Port GPIOA
#define SP_A2_Pin GPIO_PIN_9
#define SP_A2_GPIO_Port GPIOA
#define SP_B2_Pin GPIO_PIN_10
#define SP_B2_GPIO_Port GPIOA
#define E_A1_Pin GPIO_PIN_15
#define E_A1_GPIO_Port GPIOA
#define E_B1_Pin GPIO_PIN_10
#define E_B1_GPIO_Port GPIOC
#define E_S1_Pin GPIO_PIN_11
#define E_S1_GPIO_Port GPIOC
#define SP_B5_Pin GPIO_PIN_12
#define SP_B5_GPIO_Port GPIOC
#define SP_A5_Pin GPIO_PIN_2
#define SP_A5_GPIO_Port GPIOD
#define ST_A5_Pin GPIO_PIN_4
#define ST_A5_GPIO_Port GPIOB
#define SP_A2_R_Pin GPIO_PIN_6
#define SP_A2_R_GPIO_Port GPIOB
#define SP_B2_R_Pin GPIO_PIN_7
#define SP_B2_R_GPIO_Port GPIOB
#define SP_A1_R_Pin GPIO_PIN_8
#define SP_A1_R_GPIO_Port GPIOB
#define SP_B1_R_Pin GPIO_PIN_9
#define SP_B1_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED1_Pin GPIO_PIN_15
#define LED1_GPIO_Port GPIOB

extern UART_HandleTypeDef huart2;
extern CAN_HandleTypeDef hcan;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
