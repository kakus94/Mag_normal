/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gfxsimulator.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1306.h"
#include "Motor_Control.h"
#include "LED_Strip.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile double error1;
volatile double error2;
volatile uint8_t FlagPID;
volatile uint8_t FlagRead_LedStrip;
volatile uint8_t led1;
volatile uint8_t led2;
volatile uint8_t led3;
volatile uint8_t led4;
volatile uint8_t led5;

volatile int16_t speed;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	Motor_InitTypeDef MotorLeft;
	Motor_InitTypeDef MotorRight;
	MotorPID_InitTypeDef MotorPID_Left;
	MotorPID_InitTypeDef MotorPID_Right;
	LedStrip_InitTypeDef LedStrip;
	LedStrip_Speed_InitTypeDef LedStrip_Speed;

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		while (1)
			;
	}
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI3_Init();
	MX_TIM13_Init();
	MX_TIM14_Init();
	MX_TIM4_Init();
	MX_TIM8_Init();
	MX_GFXSIMULATOR_Init();
	MX_TIM12_Init();

	/* Initialize interrupts */
	MX_NVIC_Init();
	/* USER CODE BEGIN 2 */
	ssd1306_init();
	ssd1306_clear_screen(0xFF);
	HAL_Delay(1000);
	ssd1306_clear_screen(0x00);
	ssd1306_hello_word();
	printf("Start\n");
	ITM_SendChar('A');

	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);

	vMotor_init(&MotorLeft, &MotorRight);
	vMotorPID_init(&MotorPID_Left, &MotorPID_Right);

	HAL_Delay(2000);
	vMotor_Control(&MotorLeft, Forward);
	vMotor_Control(&MotorRight, Forward);

	HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
	HAL_TIM_Base_Start_IT(&htim12);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (FlagRead_LedStrip >= 50)
		{
			FlagRead_LedStrip = 0;
			vLedStrip_ReadStatus(&LedStrip);
			LedStrip_Speed = vLed_control(&LedStrip);
			if ((speed + LedStrip_Speed.LeftSpeed) >= 0)
			{
				MotorPID_Left.ValueTask = speed + LedStrip_Speed.LeftSpeed;
			} else
			{
				MotorPID_Left.ValueTask = 0;
			}
			if ((speed + LedStrip_Speed.RightSpeed) >= 0)
			{
				MotorPID_Right.ValueTask = speed + LedStrip_Speed.RightSpeed;
			} else
			{
				MotorPID_Right.ValueTask = 0;
			}
		}

		if (FlagPID >= 5)
		{
			FlagPID = 0;
			vMotorPID_Control(&MotorPID_Left, &MotorLeft);
			vMotorPID_Control(&MotorPID_Right, &MotorRight);

			error1 = MotorPID_Left.ExecutionValue;
			error2 = MotorPID_Right.ExecutionValue;

			vMotor_SetPWM(&MotorLeft, error1);
			vMotor_SetPWM(&MotorRight, error2);

			uClearCounter(MotorLeft.Tim_Encoder);
			uClearCounter(MotorRight.Tim_Encoder);
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 160;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief NVIC Configuration.
 * @retval None
 */
static void MX_NVIC_Init(void)
{
	/* TIM8_BRK_TIM12_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM12)
		FlagPID++;
	FlagRead_LedStrip++;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
