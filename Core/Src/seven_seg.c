/*
 * seven_seg.c
 *
 *  Created on: Nov 6, 2022
 *      Author: PC
 */

#include "seven_seg.h"
#include "main.h"

#define ENABLE 	0
#define DISABLE 1
#define LED_ON 	0
#define LED_OFF 1

int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

void display7SEG(int num)
{
	int SEVEN_SEG_array[10][7] = {{LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_OFF},
						   	   	  {LED_OFF, LED_ON, LED_ON, LED_OFF, LED_OFF, LED_OFF, LED_OFF},
								  {LED_ON, LED_ON, LED_OFF, LED_ON, LED_ON, LED_OFF, LED_ON},
								  {LED_ON, LED_ON, LED_ON, LED_ON, LED_OFF, LED_OFF, LED_ON},
								  {LED_OFF, LED_ON, LED_ON, LED_OFF, LED_OFF, LED_ON, LED_ON},
								  {LED_ON, LED_OFF, LED_ON, LED_ON, LED_OFF, LED_ON, LED_ON},
								  {LED_ON, LED_OFF, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON},
								  {LED_ON, LED_ON, LED_ON, LED_OFF, LED_OFF, LED_OFF, LED_OFF},
								  {LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON},
								  {LED_ON, LED_ON, LED_ON, LED_ON, LED_OFF, LED_ON, LED_ON}};
	HAL_GPIO_WritePin(SEVEN_SEG_a_GPIO_Port, SEVEN_SEG_a_Pin, SEVEN_SEG_array[num][0]);
	HAL_GPIO_WritePin(SEVEN_SEG_b_GPIO_Port, SEVEN_SEG_b_Pin, SEVEN_SEG_array[num][1]);
	HAL_GPIO_WritePin(SEVEN_SEG_c_GPIO_Port, SEVEN_SEG_c_Pin, SEVEN_SEG_array[num][2]);
	HAL_GPIO_WritePin(SEVEN_SEG_d_GPIO_Port, SEVEN_SEG_d_Pin, SEVEN_SEG_array[num][3]);
	HAL_GPIO_WritePin(SEVEN_SEG_e_GPIO_Port, SEVEN_SEG_e_Pin, SEVEN_SEG_array[num][4]);
	HAL_GPIO_WritePin(SEVEN_SEG_f_GPIO_Port, SEVEN_SEG_f_Pin, SEVEN_SEG_array[num][5]);
	HAL_GPIO_WritePin(SEVEN_SEG_g_GPIO_Port, SEVEN_SEG_g_Pin, SEVEN_SEG_array[num][6]);
}

void update7SEG(int index)
{
	switch(index)
	{
	case 0:
		//Display the first 7 SEG with led_buffer[0]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, ENABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 1:
		//Display the second 7 SEG with led_buffer[1]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, ENABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 2:
		//Display the third 7 SEG with led_buffer[2]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, ENABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, DISABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 3:
		//Display the forth 7 SEG with led_buffer[3]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, DISABLE);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, DISABLE);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, DISABLE);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, ENABLE);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	}
}

void updateLedBuffer(int config, int value)
{
	switch (config)
	{
	case SEVEN_SEG_PAIR_1_2:
		led_buffer[0] = value / 10;
		led_buffer[1] = value % 10;
		break;
	case SEVEN_SEG_PAIR_3_4:
		led_buffer[2] = value / 10;
		led_buffer[3] = value % 10;
		break;
	}
}

