/*
 * ESP_8266_driver.c
 *
 *  Created on: 04.04.2019
 *      Author: mprze
 */

#include "ESP_8266_driver.h"
#include "string.h"


uint8_t Command[256];
uint8_t map_size;

/**
 * Function set default configurations for ESP_8266
 */
HAL_StatusTypeDef mySEP8266_Restore(uint8_t mode)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	return status;
}

/**
 * Set mode in ESP_8266
 */
HAL_StatusTypeDef mySEP8266_SetMode(uint8_t mode)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	return status;
}


/**
 * Function init ESP_8266
 */
void myESP_8266_InitServer(uint8_t mode, char *SSID, char* PASSWORD,
		uint16_t Port)
{

	/* Copy UART handle variable */
	memcpy(&esp_uart, &huart1, sizeof(huart1));

	/* SET CH_PD and RST to Vcc */

	/* TODO */
//	HAL_GPIO_WritePin(ESP_8266_CH_PD_GPIO_Port, ESP_8266_CH_PD_Pin, SET);
//	HAL_GPIO_WritePin(ESP_8266_RST_GPIO_Port, ESP_8266_RST_Pin, SET);

	/* Reset device */
	map_size = sprintf(&Command, "AT+RST\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(200);

	/* Set device mode */
	map_size = sprintf(&Command, "AT+CWMODE_DEF=%d\r\n", mode);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(200);

	/* Connection to AP */
	map_size = sprintf(&Command, "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(5000);
	/* Set current IP, gateway and netmask */
	map_size = sprintf(&Command,
			"AT+CIPSTA_DEF=\"192.168.1.11\",\"192.168.1.1\",\"255.255.255.0\"\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(300);
	/* Enable multiple connections */
	map_size = sprintf(&Command, "AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(300);
	/* Create server on Port */
	map_size = sprintf(&Command, "AT+CIPSERVER=1,%d\r\n", Port);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(300);
}

/**
 *
 */
void myESP_8266_InitClient(uint8_t mode,char *SSID, char* PASSWORD,uint16_t Port)
 {
	/* Copy UART handle variable */
	memcpy(&esp_uart, &huart1, sizeof(huart1));

	/* TODO */
//	HAL_GPIO_WritePin(ESP_8266_CH_PD_GPIO_Port, ESP_8266_CH_PD_Pin, SET);
//	HAL_GPIO_WritePin(ESP_8266_RST_GPIO_Port, ESP_8266_RST_Pin, SET);

	/* Close connection  */
	map_size = sprintf(&Command, "AT+CIPCLOSE\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);

	/* Reset device */
	map_size = sprintf(&Command, "AT+RST\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);

	/* Set device mode */
	map_size = sprintf(&Command, "AT+CWMODE_DEF=%d\r\n", mode);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);

	/* Connection to AP */
	map_size = sprintf(&Command, "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n", SSID, PASSWORD);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(5000);
	/**/
	/* Get current IP, gateway and netmask */
	map_size = sprintf(&Command, "AT+CIFSR\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
	/**/

	/* Set current IP, gateway and netmask */
	map_size = sprintf(&Command,
					"AT+CIPSTA_DEF=\"192.168.1.100\",\"192.168.1.1\",\"255.255.255.0\"\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
	/* tcp conect */
//	size = sprintf(&Command, "AT+CIPSTART=\"TCP\",\"192.168.1.10\",%d\r\n", Port);
	map_size = sprintf(&Command, "AT+CIPSTART=\"TCP\",\"192.168.1.10\",%d\r\n", Port);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
}

void myESP_8266_PrepareToSending(uint32_t ServerPort)
{

	map_size = sprintf(&Command, "AT+CIPMODE=1\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(200);

	/*  */
	map_size = sprintf(&Command, "AT+CIPSEND\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(200);
}

/**
 * Function send frame
 */
void myESP8266_SendFrame(uint8_t* data, uint32_t Port)
{
	myESP_8266_PrepareToSending(Port);
	HAL_Delay(10);
	map_size = sprintf(&Command, data);

	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
}

/**
 * Function ending connection with server
 */
void myESP8266_SendEnd()
 {
	map_size = sprintf(&Command, "+++");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
	map_size = sprintf(&Command, "AT+CIPCLOSE\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(10);
}


/**
 *
 */
void myESP8266_SendFrameFromServer(uint8_t* data, uint8_t LinkID , uint8_t Length)
{
	map_size = sprintf(&Command, "AT+CIPSEND=%d,%d\r\n",LinkID,Length);
	HAL_UART_Transmit(&esp_uart, Command, map_size, 1000);
	HAL_Delay(100);
	map_size = sprintf(&Command, data);
	HAL_UART_Transmit(&esp_uart, Command, map_size,1000);
	HAL_Delay(50);
}

/**
 * Function switch to server mode and wait for data from client
 */
void myESP8266_RxMode(uint8_t ServerPort)
{
	map_size = sprintf(&Command, "AT+CIPMODE=0\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size,1000);
	HAL_Delay(300);
	map_size = sprintf(&Command, "AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(&esp_uart, Command, map_size,1000);
	HAL_Delay(300);
	/* Create server on Port */
	map_size = sprintf(&Command, "AT+CIPSERVER=1,%d\r\n",ServerPort);
	HAL_UART_Transmit(&esp_uart, Command, map_size,1000);
	HAL_Delay(300);
}


// Funkcja wysy³aj¹ca podany ci¹g znaków przez interfejs UART

void uart_write_line(UART_HandleTypeDef * handler, char * text)
{

//                HAL_UART_Transmit(handler, text, strlen(text), 1000);
//
//                HAL_UART_Transmit(handler, "\r\n", 2, 100);

}

// Funkcja wysy³aj¹ca dane przez nawi¹zane po³¹czenie TCP

// i zamykaj¹ca to po³¹czenie

void esp_send_data_and_close(UART_HandleTypeDef * uart, char mux_id,
		char * content)
{
//
//		char cmd[17];
//
//		sprintf(cmd, "AT+CIPSEND=%c,%d", mux_id, strlen(content));
//
//		uart_write_line(uart, cmd);
//
//		HAL_Delay(20);
//
//		HAL_UART_Transmit(uart, content, strlen(content), 5000);
//
//		HAL_Delay(100);
//
//		sprintf(cmd, "AT+CIPCLOSE=%c", esp_recv_mux);
//
//		uart_write_line(esp_uart, cmd);

}
