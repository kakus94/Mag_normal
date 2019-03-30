/*
 * Motor_Control.h
 *
 *  Created on: 29.03.2019
 *      Author: kkarp
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "main.h"

#define Motor_GPIO_pin1	GPIO_Motor_control1_GPIO_Port
#define Motor_Pin1		GPIO_Motor_control1_Pin

#define Motor_GPIO_pin2	GPIO_Motor_Control3_GPIO_Port
#define Motor_Pin2		GPIO_Motor_Control3_Pin

#define Motor_GPIO_pin3	GPIO_Motor_control2_GPIO_Port
#define Motor_Pin3		GPIO_Motor_control2_Pin

#define Motor_GPIO_pin4	GPIO_Motor_Control4_GPIO_Port
#define Motor_Pin4		GPIO_Motor_Control4_Pin

#define Motor1_Tim TIM4
#define Motor2_Tim TIM8

#define Motor1_PWM TIM13
#define Motor2_PWM TIM14
/*
 #define BridgeH_int1_Port	0
 #define BridgeH_int1_Pin	0

 #define BridgeH_int2_Port	0
 #define BridgeH_int2_Pin	0

 #define BridgeH_int3_Port	0
 #define BridgeH_int3_Pin	0

 #define BridgeH_int4_Port	0
 #define BridgeH_int4_Pin	0
 */

enum eBridgeControl
{
	BreakeHard, Back, Forward, BreakeSoft
};

typedef struct
{
	TIM_TypeDef* Tim_Encoder;
	TIM_TypeDef* Tim_PWM;
	GPIO_TypeDef * Motor_GPIO_int1;
	uint16_t Motor_Pin_int1;
	GPIO_TypeDef * Motor_GPIO_int2;
	uint16_t Motor_Pin_int2;
	uint8_t speed;
	uint32_t dutyPWM;
	uint32_t number_turns;
} Motor_InitTypeDef;

uint16_t uGetCounterTim(TIM_TypeDef tim);
uint8_t uClearCounter(TIM_TypeDef tim);
void vMotor_Control(Motor_InitTypeDef* motor, uint8_t eBridgeControl);
void vMotor_init(Motor_InitTypeDef* Motor_InitStruct1,
		Motor_InitTypeDef* Motor_InitStruct2);
void vMotor_SetPWM(Motor_InitTypeDef* motor, uint8_t dutyPWM);

#endif /* MOTOR_CONTROL_H_ */
