/*
 * Motor_Control.c
 *
 *  Created on: 29.03.2019
 *      Author: kkarp
 */
#include "Motor_Control.h"

uint16_t uGetCounterTim(TIM_TypeDef tim)
{
	return tim.CNT;
}

uint8_t uClearCounter(TIM_TypeDef tim)
{
	tim.CNT = 0;

	if (tim.CNT == 0)
		return 1;
	else
		return 0;
}

void vMotor_init(Motor_InitTypeDef* Motor_InitStruct1,
		Motor_InitTypeDef* Motor_InitStruct2)
{
	Motor_InitStruct1->Motor_GPIO_int1 = Motor_GPIO_pin1;
	Motor_InitStruct1->Motor_GPIO_int2 = Motor_GPIO_pin2;
	Motor_InitStruct1->Motor_Pin_int1 = Motor_Pin1;
	Motor_InitStruct1->Motor_Pin_int2 = Motor_Pin2;
	Motor_InitStruct1->number_turns = 0;
	Motor_InitStruct1->speed = 0;
	Motor_InitStruct1->Tim_Encoder = Motor1_Tim;
	Motor_InitStruct1->Tim_PWM = Motor1_PWM;

	Motor_InitStruct2->Motor_GPIO_int1 = Motor_GPIO_pin3;
	Motor_InitStruct2->Motor_GPIO_int2 = Motor_GPIO_pin4;
	Motor_InitStruct2->Motor_Pin_int1 = Motor_Pin3;
	Motor_InitStruct2->Motor_Pin_int2 = Motor_Pin4;
	Motor_InitStruct2->number_turns = 0;
	Motor_InitStruct2->speed = 0;
	Motor_InitStruct2->Tim_Encoder = Motor2_Tim;
	Motor_InitStruct2->Tim_PWM = Motor2_PWM;
}

void vMotor_Control(Motor_InitTypeDef* motor, uint8_t eBridgeControl)

{
	switch (eBridgeControl)
	{
	case BreakeHard:
		HAL_GPIO_WritePin(motor->Motor_GPIO_int1, motor->Motor_Pin_int1,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor->Motor_GPIO_int2, motor->Motor_Pin_int2,
				GPIO_PIN_RESET);
	motor->Tim_PWM->CCR1 = motor->Tim_PWM->ARR;

		break;
	case Back:
		HAL_GPIO_WritePin(motor->Motor_GPIO_int1, motor->Motor_Pin_int1,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor->Motor_GPIO_int2, motor->Motor_Pin_int2,
				GPIO_PIN_SET);
		motor->Tim_PWM->CCR1 = motor->dutyPWM;
		break;
	case Forward:
		HAL_GPIO_WritePin(motor->Motor_GPIO_int1, motor->Motor_Pin_int1,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->Motor_GPIO_int2, motor->Motor_Pin_int2,
				GPIO_PIN_RESET);
		motor->Tim_PWM->CCR1 = motor->dutyPWM;
		break;
	case BreakeSoft:
		HAL_GPIO_WritePin(motor->Motor_GPIO_int1, motor->Motor_Pin_int1,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->Motor_GPIO_int2, motor->Motor_Pin_int2,
				GPIO_PIN_SET);
		motor->Tim_PWM->CCR1 = 0;
		break;
	default:
		break;
	}

}
void vMotor_SetPWM(Motor_InitTypeDef* motor, uint8_t dutyPWM)
{
	//motor->dutyPWM = (motor->Tim_PWM->ARR / dutyPWM);
	motor->Tim_PWM->CCR1 = dutyPWM;
}
