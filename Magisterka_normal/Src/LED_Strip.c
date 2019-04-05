/*
 * LED_Strip.c
 *
 *  Created on: 04.04.2019
 *      Author: kkarp
 */

#include "LED_Strip.h"

void vLedStrip_ReadStatus(LedStrip_InitTypeDef* LedStript)
{
	LedStript->Led1_StatusPin = HAL_GPIO_ReadPin(Led1_Gpio, Led1_Pin);
	LedStript->Led2_StatusPin = HAL_GPIO_ReadPin(Led2_Gpio, Led2_Pin);
	LedStript->Led3_StatusPin = HAL_GPIO_ReadPin(Led3_Gpio, Led3_Pin);
	LedStript->Led4_StatusPin = HAL_GPIO_ReadPin(Led4_Gpio, Led4_Pin);
	LedStript->Led5_StatusPin = HAL_GPIO_ReadPin(Led5_Gpio, Led5_Pin);

	if (LedStript->Led_StatusPin != LedStript->history[LedStript->pivot])
	{
		LedStript->pivot++;
		if (LedStript->pivot >= size)
		{
			LedStript->pivot = 0;
		}
		LedStript->history[LedStript->pivot] = LedStript->Led_StatusPin;
	}
}

LedStrip_Speed_InitTypeDef vLed_control(LedStrip_InitTypeDef* LedStript)
{
	static LedStrip_Speed_InitTypeDef Motor;
	if (!LedStript->MissLineError || !LedStript->Led3_StatusPin)
	{
		switch (LedStript->Led_StatusPin)
		{
		case LS_miss:
			LedStript->MissLineError = 1;
			uint8_t TempPivot;
			uint8_t LastLine;
			TempPivot = LedStript->pivot - 1;
			if (TempPivot > size)
			{
				LastLine = LedStript->history[size - 1];
			} else
			{
				LastLine = LedStript->history[TempPivot];
			}
			if (LastLine == LS_00001)
			{
				Motor.LeftSpeed =3;
				Motor.RightSpeed = -100;
			}
			if (LastLine == LS_10000)
			{
				Motor.LeftSpeed = -100;
				Motor.RightSpeed = 3;
			}

			break;
		case LS_all:

			break;
		case LS_00001:
			Motor.LeftSpeed = 2;
			Motor.RightSpeed = -100;
			break;
		case LS_00010:
			Motor.LeftSpeed = 3;
			Motor.RightSpeed = -1;
			break;
		case LS_00011:
			Motor.LeftSpeed = 2;
			Motor.RightSpeed = -100;
			break;
		case LS_00100:
			LedStript->MissLineError =0;
			Motor.LeftSpeed = 0;
			Motor.RightSpeed = 0;
			break;
		case LS_00110:
			Motor.LeftSpeed = 2;
			Motor.RightSpeed = 0;
			break;
		case LS_01000:
			Motor.LeftSpeed = -1;
			Motor.RightSpeed = 3;
			break;
		case LS_01100:
			Motor.LeftSpeed = 0;
			Motor.RightSpeed = 2;
			break;
		case LS_10000:
			Motor.LeftSpeed = -100;
			Motor.RightSpeed = 2;
			break;
		case LS_11000:
			Motor.LeftSpeed = -100;
			Motor.RightSpeed = 2;
			break;

		default:
			break;
		}
	}
	return Motor;

}

