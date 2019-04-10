/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RFID_IRQ_Pin GPIO_PIN_5
#define RFID_IRQ_GPIO_Port GPIOF
#define RFID_RESET_Pin GPIO_PIN_4
#define RFID_RESET_GPIO_Port GPIOC
#define SPI_RFID_CS_Pin GPIO_PIN_1
#define SPI_RFID_CS_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_2
#define OLED_CS_GPIO_Port GPIOG
#define OLED_DC_Pin GPIO_PIN_3
#define OLED_DC_GPIO_Port GPIOG
#define LED_Control5_Pin GPIO_PIN_4
#define LED_Control5_GPIO_Port GPIOG
#define LED_Control4_Pin GPIO_PIN_5
#define LED_Control4_GPIO_Port GPIOG
#define LED_Control3_Pin GPIO_PIN_6
#define LED_Control3_GPIO_Port GPIOG
#define LED_Control2_Pin GPIO_PIN_7
#define LED_Control2_GPIO_Port GPIOG
#define LED_Control1_Pin GPIO_PIN_8
#define LED_Control1_GPIO_Port GPIOG
#define OLED_RES_Pin GPIO_PIN_8
#define OLED_RES_GPIO_Port GPIOC
#define GPIO_Motor_Control4_Pin GPIO_PIN_10
#define GPIO_Motor_Control4_GPIO_Port GPIOG
#define GPIO_Motor_control2_Pin GPIO_PIN_11
#define GPIO_Motor_control2_GPIO_Port GPIOG
#define GPIO_Motor_Control3_Pin GPIO_PIN_13
#define GPIO_Motor_Control3_GPIO_Port GPIOG
#define GPIO_Motor_control1_Pin GPIO_PIN_15
#define GPIO_Motor_control1_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
