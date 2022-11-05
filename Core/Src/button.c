/*
 * button.c
 *
 *  Created on: Sep 21, 2022
 *      Author: KAI
 */

#include "button.h"

#define TIME_FOR_LONG_PRESSED 300
#define LONG_PRESSED_INTERVAL 100

int KeyReg0[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimeOutForKeyPress[NO_OF_BUTTONS] = {100, 100, 100};
int TimeOutForDoublePressed[NO_OF_BUTTONS] = {25, 25, 25};
int button_flag[NO_OF_BUTTONS] = {0, 0, 0};
int button_flag_long_pressed[NO_OF_BUTTONS] = {0, 0, 0};
int button_flag_double_pressed[NO_OF_BUTTONS] = {0, 0, 0};

int isPressedBefore[NO_OF_BUTTONS] = {0, 0, 0};

int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index)
{
	if(button_flag_long_pressed[index] == 1){
		button_flag_long_pressed[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonDoublePressed(int index)
{
	if(button_flag_double_pressed[index] == 1){
		button_flag_double_pressed[index] = 0;
		return 1;
	}
	return 0;
}

void resetButtonFlag(int index)
{
	button_flag[index] = 0;
}

void subKeyProcess(int index){
	//TODO
	//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	button_flag[index] = 1;
}

void subKeyProcessLongPressed(int index)
{
	button_flag_long_pressed[index] = 1;
}

void subKeyProcessDoublePressed(int index)
{
	button_flag_double_pressed[index] = 1;
}

void getKeyInput(){
		  KeyReg2[0] = KeyReg1[0];
	 	  KeyReg1[0] = KeyReg0[0];
		  KeyReg0[0] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
		  KeyReg2[1] = KeyReg1[1];
		  KeyReg1[1] = KeyReg0[1];
		  KeyReg0[1] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
		  KeyReg2[2] = KeyReg1[2];
		  KeyReg1[2] = KeyReg0[2];
		  KeyReg0[2] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
		  for (int i = 0; i < NO_OF_BUTTONS; i++)
		  {
			  if (isPressedBefore[i] == 1 && TimeOutForDoublePressed[i] > 0) TimeOutForDoublePressed[i]--;
			  if (TimeOutForDoublePressed[i] == 0) isPressedBefore[i] = 0;
			  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){ //Press
				if (KeyReg2[i] != KeyReg3[i])
				{
				  KeyReg3[i] = KeyReg2[i];
				  if (KeyReg3[i] == PRESSED_STATE)
				  {
					  if (isPressedBefore[i] == 1)
					  {
						  subKeyProcessDoublePressed(i);
					  }
					  if (isPressedBefore[i] == 0)
					  {
						  TimeOutForKeyPress[i] = TIME_FOR_LONG_PRESSED;
						  TimeOutForDoublePressed[i] = 25;
						  subKeyProcess(i);
						  isPressedBefore[i] = 1;
					  }
				  }
				}
				else{ // Long press
				   TimeOutForKeyPress[i]--;
					if (TimeOutForKeyPress[i] == 0 && KeyReg3[i] == PRESSED_STATE){
						subKeyProcessLongPressed(i);
						TimeOutForKeyPress[i] = LONG_PRESSED_INTERVAL;
					}
				}
			  }
		  }
}

