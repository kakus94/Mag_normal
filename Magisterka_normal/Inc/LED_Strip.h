/*
 * LED_Strip.h
 *
 *  Created on: 04.04.2019
 *      Author: kkarp
 */

#ifndef LED_STRIP_H_
#define LED_STRIP_H_

#include "main.h"

/*              LED STRIP
 * **************************************
 * * LED1    LED2   LED3   LED4   LED5  *
 * **************************************
 * */

#define Led1_Gpio 	LED_Control2_GPIO_Port
#define Led1_Pin 	LED_Control2_Pin

#define Led2_Gpio 	LED_Control3_GPIO_Port
#define Led2_Pin 	LED_Control3_Pin

#define Led3_Gpio 	LED_Control4_GPIO_Port
#define Led3_Pin 	LED_Control4_Pin

#define Led4_Gpio  	LED_Control5_GPIO_Port
#define Led4_Pin 	LED_Control5_Pin

#define Led5_Gpio 	LED_Control1_GPIO_Port
#define Led5_Pin    LED_Control1_Pin

#define size 10

enum
{
	LS_miss = 0x1F,
	LS_all = 0x00,
	LS_00001 = 0x1E,
	LS_00011 = 0x1C,
	LS_00010 = 0x1D,
	LS_00110 = 0x19,
	LS_00100 = 0x1B,
	LS_01100 = 0x13,
	LS_01000 = 0x17,
	LS_11000 = 0x07,
	LS_10000 = 0x0F,
	LS_miss_L = 0xF0,
	LS_miss_R = 0xF1
} LedStrip_StatusPinEnum;

typedef struct
{
	uint8_t history[10];
	uint8_t pivot;
	uint8_t MissLineError;
	union
	{
		uint8_t Led_StatusPin;
		struct
		{
			uint8_t Led1_StatusPin :1;
			uint8_t Led2_StatusPin :1;
			uint8_t Led3_StatusPin :1;
			uint8_t Led4_StatusPin :1;
			uint8_t Led5_StatusPin :1;
			uint8_t unused :3;
		};
	};
} LedStrip_InitTypeDef;

typedef struct
{
	int8_t LeftSpeed;
	int8_t RightSpeed;
	uint8_t Action;

} LedStrip_Speed_InitTypeDef;

void vLedStrip_ReadStatus(LedStrip_InitTypeDef* LedStript);
LedStrip_Speed_InitTypeDef vLed_control(LedStrip_InitTypeDef* LedStript);
void vLedStrip_Init(LedStrip_InitTypeDef* ledStrip_InitTypeDef);

#endif /* LED_STRIP_H_ */
