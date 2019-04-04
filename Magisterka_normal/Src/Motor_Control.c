/*
 * Motor_Control.c
 *
 *  Created on: 29.03.2019
 *      Author: kkarp
 */
#include "Motor_Control.h"

uint16_t uGetCounterTim(TIM_TypeDef* tim)
{
	return tim->CNT;
}
uint8_t uClearCounter(TIM_TypeDef* tim)
{
	tim->CNT = 0;

//	if (tim->CNT == 0)
//		return 1;
//	else
//		return 0;
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
	Motor_InitStruct1->Tim_Encoder = Motor1_Encoder;
	Motor_InitStruct1->Tim_PWM = Motor1_PWM;

	Motor_InitStruct2->Motor_GPIO_int1 = Motor_GPIO_pin3;
	Motor_InitStruct2->Motor_GPIO_int2 = Motor_GPIO_pin4;
	Motor_InitStruct2->Motor_Pin_int1 = Motor_Pin3;
	Motor_InitStruct2->Motor_Pin_int2 = Motor_Pin4;
	Motor_InitStruct2->number_turns = 0;
	Motor_InitStruct2->speed = 0;
	Motor_InitStruct2->Tim_Encoder = Motor2_Encoder;
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
	motor->dutyPWM = (motor->Tim_PWM->ARR * dutyPWM) / 100.0;
	motor->Tim_PWM->CCR1 = motor->dutyPWM;

//	motor->dutyPWM = (motor->Tim_PWM->ARR * dutyPWM) / 100.0;
//		if (dutyPWM != 0)
//		{
//			motor->Tim_PWM->CCR1 = motor->dutyPWM;
//		} else
//		{
//			HAL_GPIO_WritePin(motor->Motor_GPIO_int1, motor->Motor_Pin_int1,
//					GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(motor->Motor_GPIO_int2, motor->Motor_Pin_int2,
//					GPIO_PIN_RESET);
//			motor->Tim_PWM->CCR1 = motor->Tim_PWM->ARR;
//		}
}

void vMotorPID_init(MotorPID_InitTypeDef* PID1, MotorPID_InitTypeDef* PID2)
{
	PID1->e_last = 0;
	PID1->e_sum = 0;
	PID1->e_sumMax = MaxPIDki;
	PID1->kp = KdValue1;
	PID1->ki = KiValue1;
	PID1->kd = KdValue1;
	PID1->ValueTask = 90;

	PID2->e_last = 0;
	PID2->e_sum = 0;
	PID2->e_sumMax = MaxPIDki;
	PID2->kp = KdValue2;
	PID2->ki = KiValue2;
	PID2->kd = KdValue2;
	PID2->ValueTask = 90;
}
void vMotorPID_Control(MotorPID_InitTypeDef* MotorPID, Motor_InitTypeDef* Motor)
{
	MotorPID->e = MotorPID->ValueTask - uGetCounterTim(Motor->Tim_Encoder);
	MotorPID->e_sum += MotorPID->e;
	if (MotorPID->e_sum > MotorPID->e_sumMax)
		MotorPID->e_sum = MotorPID->e_sumMax;

	MotorPID->ExecutionValue = MotorPID->kp * MotorPID->e
			+ MotorPID->ki * MotorPID->e_sum
			+ MotorPID->kd * (MotorPID->e - MotorPID->e_last);

	if (MotorPID->ValueTask == 0)
	{
		MotorPID->e_sum = 0;
		MotorPID->ExecutionValue = 0;
	}
}
