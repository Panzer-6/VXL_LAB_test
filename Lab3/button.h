/*
 * button.h
 *
 *  Created on: Sep 21, 2022
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NO_OF_BUTTONS 3

extern int button1_flag;

int isButtonPressed(int index);
int isButtonPressed1s(int index);
void resetButtonFlag(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */
