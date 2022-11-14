/*
 * task.c
 *
 *  Created on: Nov 12, 2022
 *      Author: PC
 */
#include "main.h"

void toggleRedLed()
{
	HAL_GPIO_TogglePin(REDLED_GPIO_Port, REDLED_Pin);
}

void toggleGreenLed()
{
	HAL_GPIO_TogglePin(GREENLED_GPIO_Port, GREENLED_Pin);
}

void toggleYellowLed()
{
	HAL_GPIO_TogglePin(YELLOWLED_GPIO_Port, YELLOWLED_Pin);
}

void toggleBlueLed()
{
	HAL_GPIO_TogglePin(BLUELED_GPIO_Port, BLUELED_Pin);
}

void toggleOrangeLed()
{
	HAL_GPIO_TogglePin(ORANGELED_GPIO_Port, ORANGELED_Pin);
}

