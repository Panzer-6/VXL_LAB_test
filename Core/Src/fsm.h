/*
 * fsm.h
 *
 *  Created on: Nov 20, 2022
 *      Author: PC
 */
#include "main.h"

#ifndef SRC_FSM_H_
#define SRC_FSM_H_

#define MAX_BUFFER_SIZE 2
uint8_t buffer[MAX_BUFFER_SIZE];
int index_buffer;
int receive_flag;
uint8_t temp;
int RST_flag;
int OK_flag;


void command_parser_fsm(UART_HandleTypeDef* huart2);
void uart_communication_fsm(UART_HandleTypeDef* huart2, ADC_HandleTypeDef* hadc1);

#endif /* SRC_FSM_H_ */
