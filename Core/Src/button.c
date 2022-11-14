/*
 * button.c
 *
 *  Created on: Sep 21, 2022
 *      Author: KAI
 */

#include "button.h"

#define FLAG_ON 				1
#define FLAG_OFF 				0
#define TIMEOUT					0
#define TIME_FOR_LONG_PRESSED 	100
#define LONG_PRESS_INTERVAL		100

int KeyReg0[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[NO_OF_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int TimeOutForKeyPress[NO_OF_BUTTONS] = {500, 500, 500};
int button_flag[NO_OF_BUTTONS] = {0, 0, 0};
int button_flag_1s[NO_OF_BUTTONS] = {0, 0, 0};

GPIO_TypeDef* button_port[NO_OF_BUTTONS] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port};
uint16_t button_pin[NO_OF_BUTTONS] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin};

int isButtonPressed(int index){
	if(button_flag[index] == FLAG_ON){
		button_flag[index] = FLAG_OFF;
		return 1;
	}
	return 0;
}

int isButtonPressed1s(int index)
{
	if(button_flag_1s[index] == FLAG_ON){
		button_flag_1s[index] = FLAG_OFF;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	//TODO
	//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	button_flag[index] = FLAG_ON;
}

void subKeyProcess1s(int index)
{
	button_flag_1s[index] = FLAG_ON;
}

void getKeyInput(){
		  for (int i = 0; i < NO_OF_BUTTONS; i++)
		  {
			  KeyReg2[i] = KeyReg1[i];
			  KeyReg1[i] = KeyReg0[i];
			  KeyReg0[i] = HAL_GPIO_ReadPin(button_port[i], button_pin[i]);
			  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){ //Press
				if (KeyReg2[i] != KeyReg3[i]){
				  KeyReg3[i] = KeyReg2[i];

				  if (KeyReg3[i] == PRESSED_STATE){
					TimeOutForKeyPress[i] = TIME_FOR_LONG_PRESSED;
					subKeyProcess(i);
				  }
				}else{ // Long press
				   TimeOutForKeyPress[i]--;
					if (TimeOutForKeyPress[i] == TIMEOUT && KeyReg3[i] == PRESSED_STATE){
						subKeyProcess1s(i);
						TimeOutForKeyPress[i] = LONG_PRESS_INTERVAL;
					  //KeyReg3[i] = NORMAL_STATE;
					  //KeyReg2[i] = NORMAL_STATE;
					  //KeyReg1[i] = NORMAL_STATE;
					}
				}
			  }
		  }
}

