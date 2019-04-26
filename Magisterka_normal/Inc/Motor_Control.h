/*
 * Motor_Control.h
 *
 *  Created on: 29.03.2019
 *      Author: kkarp
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "main.h"

#define MotorLeft_GPIO_pin1	GPIO_Motor_control1_GPIO_Port
#define MotorLeft_Pin1		GPIO_Motor_control1_Pin

#define MotorLeft_GPIO_pin2	GPIO_Motor_Control4_GPIO_Port
#define MotorLeft_Pin2		GPIO_Motor_Control4_Pin

#define MotorRight_GPIO_pin1	GPIO_Motor_control2_GPIO_Port
#define MotorRight_Pin1		GPIO_Motor_control2_Pin

#define MotorRight_GPIO_pin2	GPIO_Motor_Control3_GPIO_Port
#define MotorRight_Pin2		GPIO_Motor_Control3_Pin

#define MotorLeft_Encoder TIM4
#define MotorRight_Encoder TIM8

#define MotorLeft_PWM TIM13
#define MotorRight_PWM TIM14
//PID
#define MaxPIDki 10000
#define KpValue1	3
#define KiValue1	0.5
#define KdValue1	-0.03

#define KpValue2	3
#define KiValue2	0.5
#define KdValue2	-0.03
//END PID

enum eBridgeControl
{
  BreakeHard, Back, Forward, BreakeSoft
};

enum eActionReaction
{
  rotationInPlace_Left,
  rotationInPlace_Right,
  turn_Left,
  turn_Right,
  move_Back,
  move_Forward
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
  uint8_t clear_PID;
} Motor_InitTypeDef;

typedef struct
{
  float kp;
  float ki;
  float kd;
  float e;
  float e_last;
  uint16_t e_sum;
  float e_sumMax;
  float ValueTask;
  float ExecutionValue;

} MotorPID_InitTypeDef;

uint16_t uGetCounterTim(TIM_TypeDef* tim);
HAL_StatusTypeDef vClearCounter(TIM_TypeDef* tim);
void vMotor_Control(Motor_InitTypeDef* motor, uint8_t eBridgeControl);
void vMotor_init(Motor_InitTypeDef* Motor_InitStruct1,
    Motor_InitTypeDef* Motor_InitStruct2);
void vMotor_SetPWM(Motor_InitTypeDef* motor, uint8_t dutyPWM);
void vMotorAction_LedStrip(Motor_InitTypeDef* LeftMotor,
    Motor_InitTypeDef* RightMotor, uint8_t action);

//PID implementation
void vMotorPID_Control(MotorPID_InitTypeDef* MotorPID, Motor_InitTypeDef* Motor);
void vMotorPID_init(MotorPID_InitTypeDef* PID1, MotorPID_InitTypeDef* PID2);
//END PID

#endif /* MOTOR_CONTROL_H_ */
