/*
 * input_processing.c
 *
 *  Created on: Oct 27, 2022
 *      Author: PC
 */
#include "main.h"
//#include "input_reading.h"
#include "button.h"
#include "timer.h"
#include "seven_seg.h"

#define RED_DEFAULT_DUR 	5000
#define AMBER_DEFAULT_DUR 	2000
#define GREEN_DEFAULT_DUR 	3000
#define FIRST_TRAFFIC		0
#define SECOND_TRAFFIC		1
#define LED_ON 				1
#define LED_OFF 			0
#define SCANNING_DUR		250
#define BLINKING_DUR		250
#define START				10
#define SEC_TO_MS			1000

GPIO_TypeDef* RED_LED_PORT[2] = {RED_LED_0_GPIO_Port, RED_LED_1_GPIO_Port};
GPIO_TypeDef* AMBER_LED_PORT[2] = {AMBER_LED_0_GPIO_Port, AMBER_LED_1_GPIO_Port};
GPIO_TypeDef* GREEN_LED_PORT[2] = {GREEN_LED_0_GPIO_Port, GREEN_LED_1_GPIO_Port};

uint16_t RED_LED_PIN[2] = {RED_LED_0_Pin, RED_LED_1_Pin};
uint16_t AMBER_LED_PIN[2] = {AMBER_LED_0_Pin, AMBER_LED_1_Pin};
uint16_t GREEN_LED_PIN[2] = {GREEN_LED_0_Pin, GREEN_LED_1_Pin};

void UPDATE_RED_LED(int index, int state)
{
	HAL_GPIO_WritePin(RED_LED_PORT[index], RED_LED_PIN[index], state);
}

void UPDATE_AMBER_LED(int index, int state)
{
	HAL_GPIO_WritePin(AMBER_LED_PORT[index], AMBER_LED_PIN[index], state);
}

void UPDATE_GREEN_LED(int index, int state)
{
	HAL_GPIO_WritePin(GREEN_LED_PORT[index], GREEN_LED_PIN[index], state);
}

enum Button{BUTTON1, BUTTON2, BUTTON3};
enum Mode{MODE_1, MODE_2, MODE_3, MODE_4};
enum TrafficState{INIT, AUTO_RED, AUTO_AMBER, AUTO_GREEN};
enum Mode mode = MODE_1;
enum TrafficState trafficState[2] = {INIT, INIT};
enum ModeSubstate {SUBSTATE_INIT, NORMAL};

int red_dur = RED_DEFAULT_DUR;
int amber_dur = AMBER_DEFAULT_DUR;
int green_dur = GREEN_DEFAULT_DUR;

int red_state[2] = {LED_ON, LED_OFF};
int amber_state[2] = {LED_OFF, LED_OFF};
int green_state[2] = {LED_OFF, LED_ON};

enum ModeSubstate mode_2_state = SUBSTATE_INIT;
enum ModeSubstate mode_3_state = SUBSTATE_INIT;
enum ModeSubstate mode_4_state = SUBSTATE_INIT;

int red_dur_input = 0;
int amber_dur_input = 0;
int green_dur_input = 0;

void fsm_for_input_processing(void)
{
	switch (mode)
	{
	case MODE_1:
		//TODO
		if (isButtonPressed(BUTTON1)){
			//button_reset(BUTTON1);
			mode_2_state = SUBSTATE_INIT;
			mode = MODE_2;
		}
		switch (trafficState[FIRST_TRAFFIC])
		{
		case INIT:
				trafficState[FIRST_TRAFFIC] = AUTO_RED;
				setTimer(TRAFFIC_0_TIMER, red_dur);
				setTimer(SCANNING_TIMER, 10);
				red_state[0] = LED_ON;
				amber_state[0] = LED_OFF;
				green_state[0] = LED_OFF;
			break;
		case AUTO_RED:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[FIRST_TRAFFIC] = AUTO_GREEN;
				setTimer(TRAFFIC_0_TIMER, green_dur);
				red_state[FIRST_TRAFFIC] = LED_OFF;
				amber_state[FIRST_TRAFFIC] = LED_OFF;
				green_state[FIRST_TRAFFIC] = LED_ON;
			}
			break;
		case AUTO_AMBER:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[FIRST_TRAFFIC] = AUTO_RED;
				setTimer(TRAFFIC_0_TIMER, red_dur);
				red_state[FIRST_TRAFFIC] = LED_ON;
				amber_state[FIRST_TRAFFIC] = LED_OFF;
				green_state[FIRST_TRAFFIC] = LED_OFF;
			}
			break;
		case AUTO_GREEN:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[FIRST_TRAFFIC] = AUTO_AMBER;
				setTimer(TRAFFIC_0_TIMER, amber_dur);
				red_state[FIRST_TRAFFIC] = LED_OFF;
				amber_state[FIRST_TRAFFIC] = LED_ON;
				green_state[FIRST_TRAFFIC] = LED_OFF;
			}
			break;
		}
		UPDATE_RED_LED(FIRST_TRAFFIC, red_state[FIRST_TRAFFIC]);
		UPDATE_AMBER_LED(FIRST_TRAFFIC, amber_state[FIRST_TRAFFIC]);
		UPDATE_GREEN_LED(FIRST_TRAFFIC, green_state[FIRST_TRAFFIC]);
		switch (trafficState[SECOND_TRAFFIC])
		{
		case INIT:
				trafficState[SECOND_TRAFFIC] = AUTO_GREEN;
				setTimer(TRAFFIC_1_TIMER, green_dur);
				red_state[SECOND_TRAFFIC] = LED_OFF;
				amber_state[SECOND_TRAFFIC] = LED_OFF;
				green_state[SECOND_TRAFFIC] = LED_ON;
			break;
		case AUTO_RED:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[SECOND_TRAFFIC] = AUTO_GREEN;
				setTimer(TRAFFIC_1_TIMER, green_dur);
				red_state[SECOND_TRAFFIC] = LED_OFF;
				amber_state[SECOND_TRAFFIC] = LED_OFF;
				green_state[SECOND_TRAFFIC] = LED_ON;
			}
			break;
		case AUTO_AMBER:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[SECOND_TRAFFIC] = AUTO_RED;
				setTimer(TRAFFIC_1_TIMER, red_dur);
				red_state[SECOND_TRAFFIC] = LED_ON;
				amber_state[SECOND_TRAFFIC] = LED_OFF;
				green_state[SECOND_TRAFFIC] = LED_OFF;
			}
			break;
		case AUTO_GREEN:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[SECOND_TRAFFIC] = AUTO_AMBER;
				setTimer(TRAFFIC_1_TIMER, amber_dur);
				red_state[SECOND_TRAFFIC] = LED_OFF;
				amber_state[SECOND_TRAFFIC] = LED_ON;
				green_state[SECOND_TRAFFIC] = LED_OFF;
			}
			break;
		}
		UPDATE_RED_LED(SECOND_TRAFFIC, red_state[SECOND_TRAFFIC]);
		UPDATE_AMBER_LED(SECOND_TRAFFIC, amber_state[SECOND_TRAFFIC]);
		UPDATE_GREEN_LED(SECOND_TRAFFIC, green_state[SECOND_TRAFFIC]);

		if (timer_timeout(SCANNING_TIMER))
		{
			updateLedBuffer(SEVEN_SEG_PAIR_1_2, timer_remaining(TRAFFIC_0_TIMER));
			updateLedBuffer(SEVEN_SEG_PAIR_3_4, timer_remaining(TRAFFIC_1_TIMER));
			if (index_led >= MAX_LED) index_led = 0;
			update7SEG(index_led++);
			setTimer(SCANNING_TIMER, SCANNING_DUR);
		}
		break;
	case MODE_2:
		//button_reset(BUTTON1);
		if (isButtonPressed(BUTTON1))
		{
			mode_3_state = SUBSTATE_INIT;
			mode = MODE_3;
		}
		switch (mode_2_state) {
			case SUBSTATE_INIT:
				mode_2_state = NORMAL;
				setTimer(BLINKING_TIMER, BLINKING_DUR);
				setTimer(SCANNING_TIMER, START);
				index_led = 0;
				UPDATE_RED_LED(FIRST_TRAFFIC, LED_ON);
				UPDATE_AMBER_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_GREEN_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_RED_LED(SECOND_TRAFFIC, LED_ON);
				UPDATE_AMBER_LED(SECOND_TRAFFIC, LED_OFF);
				UPDATE_GREEN_LED(SECOND_TRAFFIC, LED_OFF);
				break;
			case NORMAL:
				if (timer_timeout(BLINKING_TIMER))
				{
					setTimer(BLINKING_TIMER, BLINKING_DUR);
					HAL_GPIO_TogglePin(RED_LED_0_GPIO_Port, RED_LED_0_Pin);
					HAL_GPIO_TogglePin(RED_LED_1_GPIO_Port, RED_LED_1_Pin);
				}
				//button_reset(BUTTON2);
				if (isButtonPressed(BUTTON2))
				{
					//button_reset(BUTTON2);
					red_dur_input++;
					if (red_dur_input > 99) red_dur_input -= 100;
				}
				if (isButtonPressed1s(BUTTON2))
				{
					//button_reset(BUTTON2);
					red_dur_input += 10;
					if (red_dur_input > 99) red_dur_input -= 100;
				}
				if (isButtonPressed(BUTTON3)) red_dur = red_dur_input * SEC_TO_MS;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, SCANNING_DUR);
					updateLedBuffer(SEVEN_SEG_PAIR_1_2, 2);
					updateLedBuffer(SEVEN_SEG_PAIR_3_4, red_dur_input);
					if (index_led >= MAX_LED) index_led = 0;
					update7SEG(index_led++);
				}
				break;
			default:
				break;
		}
		break;
	case MODE_3:
		//button_reset(BUTTON1);
		if (isButtonPressed(BUTTON1))
		{
			mode_4_state = SUBSTATE_INIT;
			mode = MODE_4;
		}
		switch (mode_3_state) {
			case SUBSTATE_INIT:
				mode_3_state = NORMAL;
				setTimer(BLINKING_TIMER, BLINKING_DUR);
				setTimer(SCANNING_TIMER, START);
				index_led = 0;
				UPDATE_RED_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_AMBER_LED(FIRST_TRAFFIC, LED_ON);
				UPDATE_GREEN_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_RED_LED(SECOND_TRAFFIC, LED_OFF);
				UPDATE_AMBER_LED(SECOND_TRAFFIC, LED_ON);
				UPDATE_GREEN_LED(SECOND_TRAFFIC, LED_OFF);
				break;
			case NORMAL:
				if (timer_timeout(BLINKING_TIMER))
				{
					setTimer(BLINKING_TIMER, BLINKING_DUR);
					HAL_GPIO_TogglePin(AMBER_LED_0_GPIO_Port, AMBER_LED_0_Pin);
					HAL_GPIO_TogglePin(AMBER_LED_1_GPIO_Port, AMBER_LED_1_Pin);
				}
				if (isButtonPressed(BUTTON2))
				{
					//button_reset(BUTTON2);
					amber_dur_input++;
					if (amber_dur_input > 99) amber_dur_input -= 100;
				}
				if (isButtonPressed1s(BUTTON2))
				{
					//button_reset(BUTTON2);
					amber_dur_input += 10;
					if (amber_dur_input > 99) amber_dur_input -= 100;
				}
				if (isButtonPressed(BUTTON3)) amber_dur = amber_dur_input * SEC_TO_MS;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, SCANNING_DUR);
					updateLedBuffer(SEVEN_SEG_PAIR_1_2, 3);
					updateLedBuffer(SEVEN_SEG_PAIR_3_4, amber_dur_input);
					if (index_led >= MAX_LED) index_led = 0;
					update7SEG(index_led++);
				}
				break;
			default:
				break;
		}
		break;
	case MODE_4:
		//button_reset(BUTTON1);
		if (isButtonPressed(BUTTON1))
		{
			trafficState[0] = INIT;
			trafficState[1] = INIT;
			mode = MODE_1;
		}
		switch (mode_4_state) {
			case SUBSTATE_INIT:
				mode_4_state = NORMAL;
				setTimer(BLINKING_TIMER, BLINKING_DUR);
				setTimer(SCANNING_TIMER, START);
				index_led = 0;
				UPDATE_RED_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_AMBER_LED(FIRST_TRAFFIC, LED_OFF);
				UPDATE_GREEN_LED(FIRST_TRAFFIC, LED_ON);
				UPDATE_RED_LED(SECOND_TRAFFIC, LED_OFF);
				UPDATE_AMBER_LED(SECOND_TRAFFIC, LED_OFF);
				UPDATE_GREEN_LED(SECOND_TRAFFIC, LED_ON);
				break;
			case NORMAL:
				if (timer_timeout(BLINKING_TIMER))
				{
					setTimer(BLINKING_TIMER, BLINKING_DUR);
					HAL_GPIO_TogglePin(GREEN_LED_0_GPIO_Port, GREEN_LED_0_Pin);
					HAL_GPIO_TogglePin(GREEN_LED_1_GPIO_Port, GREEN_LED_1_Pin);
				}
				if (isButtonPressed(BUTTON2))
				{
					//button_reset(BUTTON2);
					green_dur_input++;
					if (amber_dur_input > 99) green_dur_input -= 100;
				}
				if (isButtonPressed1s(BUTTON2))
				{
					//button_reset(BUTTON2);
					green_dur_input += 10;
					if (green_dur_input > 99) green_dur_input -= 100;
				}
				if (isButtonPressed(BUTTON3)) green_dur = green_dur_input * SEC_TO_MS;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, SCANNING_DUR);
					updateLedBuffer(SEVEN_SEG_PAIR_1_2, 4);
					updateLedBuffer(SEVEN_SEG_PAIR_3_4, green_dur_input);
					if (index_led >= MAX_LED) index_led = 0;
					update7SEG(index_led++);
				}
				break;
			default:
				break;
		}
		break;
	}
}
