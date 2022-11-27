/*
 * fsm.c
 *
 *  Created on: Nov 20, 2022
 *      Author: PC
 */

#include "fsm.h"
#include "timer.h"


#define IDLE 0
#define CMD_WAITING 1
#define CMD_WAITING_O 2
#define CMD_WAITING_R 3
#define CMD_WAITING_RS 4
#define CMD_CONFIRM 5

enum CMD {NON, RST, OK};

int cmdParserStatus = IDLE;
int ADC_value = -1;
int timeout_counter = 3;
enum CMD cmd = NON;

void command_parser_fsm(UART_HandleTypeDef* huart2)
{
	char writeStr[10];
	switch (cmdParserStatus)
	{
	case IDLE:
		if (buffer[index_buffer - 1] == '!')
		{
			cmdParserStatus = CMD_WAITING;
			index_buffer--;
		}
		break;
	case CMD_WAITING:
		if (buffer[index_buffer - 1] == 'O')
		{
			cmdParserStatus = CMD_WAITING_O;
		}
		else if (buffer[index_buffer - 1] == 'R')
		{
			cmdParserStatus = CMD_WAITING_R;
		}
		else cmdParserStatus = IDLE;
		index_buffer--;
		break;
//-----------------------------------------------------
	case CMD_WAITING_O:
		if (buffer[index_buffer - 1] == 'K')
		{
			cmdParserStatus = CMD_CONFIRM;
			cmd = OK;
		}
		else cmdParserStatus = IDLE;
		index_buffer--;
		break;
//-----------------------------------------------------
	case CMD_WAITING_R:
		if (buffer[index_buffer - 1] == 'S')
		{
			cmdParserStatus = CMD_WAITING_RS;
		}
		else cmdParserStatus = IDLE;
		index_buffer--;
		break;
	case CMD_WAITING_RS:
		if (buffer[index_buffer - 1] == 'T')
		{
			cmd = RST;
			cmdParserStatus = CMD_CONFIRM;
		}
		else cmdParserStatus = IDLE;
		index_buffer--;
		break;
//-----------------------------------------------------
	case CMD_CONFIRM:
			if (buffer[index_buffer - 1] == '#')
			{
				if (cmd == OK) OK_flag = 1;
				if (cmd == RST)
				{
					setTimer(0, 10);
					RST_flag = 1;
				}
				cmd = NON;
			}
			cmdParserStatus = IDLE;
			index_buffer--;
			break;
	default:
		break;
	}
}

void uart_communication_fsm(UART_HandleTypeDef* huart2, ADC_HandleTypeDef* hadc1)
{
	char writeStr[50];
	if (RST_flag == 1)
	{

		//HAL_UART_Transmit(huart2, writeStr, sprintf(writeStr, "RST\n"), 1000);
		//ADC_value = HAL_ADC_GetValue(&hadc1);
			//HAL_UART_Transmit(huart2, writeStr, sprintf(writeStr, "Different\n"), 1000);
		if (timer_timeout(0))
		{
			ADC_value = HAL_ADC_GetValue(hadc1);
			HAL_UART_Transmit(huart2, writeStr, sprintf(writeStr, "!ADC=%d#\r\n", ADC_value), 1000);
			setTimer(0, 3000);
		}

		//RST_flag = 0;
		//ADC_value = HAL_ADC_GetValue(&hadc1);
	}
	if (OK_flag == 1)
	{
		OK_flag = 0;
		RST_flag = 0;
		ADC_value = -1;
	}
}
