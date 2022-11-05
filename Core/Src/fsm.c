/*
 * fsm.c
 *
 *  Created on: Nov 5, 2022
 *      Author: PC
 */

#include "timer.h"
#include "button.h"
#include "seven_seg.h"

#define BLINKING_DURATION 	1000
#define TIMEOUT_DURATION	10000
#define COUNTDOWN_DURATION	1000
#define START_DURATION		10

enum STATUS {INIT, NORMAL, RES, INC, DEC};
enum STATUS fsmStatus = INIT;

int counter = 9;

void fsm_simple_button_run()
{
	if (timer_timeout(BLINKING_TIMER))
	{
		HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
		setTimer(BLINKING_TIMER, BLINKING_DURATION);
	}
	switch (fsmStatus)
	{
	case INIT:
		fsmStatus = NORMAL;
		setTimer(COUNTDOWN_TIMER, START_DURATION);
		setTimer(BLINKING_TIMER, BLINKING_DURATION);
		break;
	case NORMAL:
		if (isButtonPressed(RESET_BUTTON))
		{
			fsmStatus = RES;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter = 0;
			display7SEG(counter);
		}
		if (isButtonPressed(INC_BUTTON))
		{
			fsmStatus = INC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter++;
			if (counter > 9) counter = 0;
			display7SEG(counter);
		}
		if (isButtonPressed(DEC_BUTTON))
		{
			fsmStatus = DEC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter--;
			if (counter < 0) counter = 9;
			display7SEG(counter);
		}
		if (timer_timeout(COUNTDOWN_TIMER))
		{
			setTimer(COUNTDOWN_TIMER, COUNTDOWN_DURATION);
			display7SEG(counter);
			if (counter > 0)
			{
				counter--;
			}
		}
		break;
	case RES:
		if (isButtonPressed(INC_BUTTON))
		{
			fsmStatus = INC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter++;
			if (counter > 9) counter = 0;
			display7SEG(counter);
		}
		if (isButtonPressed(DEC_BUTTON))
		{
			fsmStatus = DEC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter--;
			if (counter < 0) counter = 9;
			display7SEG(counter);
		}
		if (timer_timeout(TIMEOUT_TIMER))
		{
			fsmStatus = NORMAL;
			setTimer(COUNTDOWN_TIMER, START_DURATION);
		}
		if (isButtonPressed(RESET_BUTTON))
		{
			counter = 0;
			display7SEG(counter);
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
		}
		break;
	case INC:
		if (isButtonPressed(RESET_BUTTON))
		{
			fsmStatus = RES;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter = 0;
			display7SEG(counter);
		}
		if (isButtonPressed(DEC_BUTTON))
		{
			fsmStatus = DEC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter--;
			if (counter < 0) counter = 9;
			display7SEG(counter);
		}
		if (timer_timeout(TIMEOUT_TIMER))
		{
			fsmStatus = NORMAL;
			setTimer(COUNTDOWN_TIMER, START_DURATION);
		}
		if (isButtonPressed(INC_BUTTON))
		{
			counter++;
			if (counter > 9) counter = 0;
			display7SEG(counter);
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
		}
		if (isButtonLongPressed(INC_BUTTON))
		{
			counter++;
			if (counter > 9) counter = 0;
			display7SEG(counter);
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
		}
		break;
	case DEC:
		if (isButtonPressed(RESET_BUTTON))
		{
			fsmStatus = RES;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter = 0;
			display7SEG(counter);
		}
		if (isButtonPressed(INC_BUTTON))
		{
			fsmStatus = INC;
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
			counter++;
			if (counter > 9) counter = 0;
			display7SEG(counter);
		}
		if (timer_timeout(TIMEOUT_TIMER))
		{
			fsmStatus = NORMAL;
			setTimer(COUNTDOWN_TIMER, START_DURATION);
		}
		if (isButtonPressed(DEC_BUTTON))
		{
			counter--;
			if (counter < 0) counter = 9;
			display7SEG(counter);
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
		}
		if (isButtonLongPressed(DEC_BUTTON))
		{
			counter--;
			if (counter < 0) counter = 9;
			display7SEG(counter);
			setTimer(TIMEOUT_TIMER, TIMEOUT_DURATION);
		}
		break;
	}
}
