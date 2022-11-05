/*
 * seven_seg.c
 *
 *  Created on: Nov 4, 2022
 *      Author: PC
 */
#include "seven_seg.h"
#include "main.h"

void display7SEG(int num)
{
	int SEVEN_SEG_array[10][7] = {{0, 0, 0, 0, 0, 0, 1},
						   	   	  {1, 0, 0, 1, 1, 1, 1},
								  {0, 0, 1, 0, 0, 1, 0},
								  {0, 0, 0, 0, 1, 1, 0},
								  {1, 0, 0, 1, 1, 0, 0},
								  {0, 1, 0, 0, 1, 0, 0},
								  {0, 1, 0, 0, 0, 0, 0},
								  {0, 0, 0, 1, 1, 1, 1},
								  {0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 0, 0}};
	HAL_GPIO_WritePin(SEVEN_SEG_a_GPIO_Port, SEVEN_SEG_a_Pin, SEVEN_SEG_array[num][0]);
	HAL_GPIO_WritePin(SEVEN_SEG_b_GPIO_Port, SEVEN_SEG_b_Pin, SEVEN_SEG_array[num][1]);
	HAL_GPIO_WritePin(SEVEN_SEG_c_GPIO_Port, SEVEN_SEG_c_Pin, SEVEN_SEG_array[num][2]);
	HAL_GPIO_WritePin(SEVEN_SEG_d_GPIO_Port, SEVEN_SEG_d_Pin, SEVEN_SEG_array[num][3]);
	HAL_GPIO_WritePin(SEVEN_SEG_e_GPIO_Port, SEVEN_SEG_e_Pin, SEVEN_SEG_array[num][4]);
	HAL_GPIO_WritePin(SEVEN_SEG_f_GPIO_Port, SEVEN_SEG_f_Pin, SEVEN_SEG_array[num][5]);
	HAL_GPIO_WritePin(SEVEN_SEG_g_GPIO_Port, SEVEN_SEG_g_Pin, SEVEN_SEG_array[num][6]);
}
/*
void update7SEG(int index)
{
	switch(index)
	{
	case 0:
		//Display the first 7 SEG with led_buffer[0]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 1:
		//Display the second 7 SEG with led_buffer[1]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 2:
		//Display the third 7 SEG with led_buffer[2]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	case 3:
		//Display the forth 7 SEG with led_buffer[3]
		//Switch EN
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		//Display LED
		display7SEG(led_buffer[index]);
		break;
	}
}

void updateLedBuffer(int timer, int duration)
{
	switch (timer)
	{
	case 0:
		led_buffer[0] = duration / 10;
		led_buffer[1] = duration % 10;
		break;
	case 1:
		led_buffer[2] = duration / 10;
		led_buffer[3] = duration % 10;
		break;
	}
}
*/


