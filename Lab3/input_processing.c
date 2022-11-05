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

#define RED_DEFAULT_DUR 	5000
#define AMBER_DEFAULT_DUR 	2000
#define GREEN_DEFAULT_DUR 	3000

#define LED_ON 				1
#define LED_OFF 			0

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

int red_dur = RED_DEFAULT_DUR;
int amber_dur = AMBER_DEFAULT_DUR;
int green_dur = GREEN_DEFAULT_DUR;

int red_state[2] = {LED_ON, LED_OFF};
int amber_state[2] = {LED_OFF, LED_OFF};
int green_state[2] = {LED_OFF, LED_ON};

int mode_2_state = 0;
int mode_3_state = 0;
int mode_4_state = 0;

int red_dur_input = 0;
int amber_dur_input = 0;
int green_dur_input = 0;

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

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

void fsm_for_input_processing(void)
{
	switch (mode)
	{
	case MODE_1:
		//TODO
		if (isButtonPressed(BUTTON1)){
			//button_reset(BUTTON1);
			mode_2_state = 0;
			mode = MODE_2;
		}
		switch (trafficState[0])
		{
		case INIT:
				trafficState[0] = AUTO_RED;
				setTimer(TRAFFIC_0_TIMER, red_dur);
				setTimer(SCANNING_TIMER, 10);
				red_state[0] = LED_ON;
				amber_state[0] = LED_OFF;
				green_state[0] = LED_OFF;
			break;
		case AUTO_RED:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[0] = AUTO_GREEN;
				setTimer(TRAFFIC_0_TIMER, green_dur);
				red_state[0] = LED_OFF;
				amber_state[0] = LED_OFF;
				green_state[0] = LED_ON;
			}
			break;
		case AUTO_AMBER:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[0] = AUTO_RED;
				setTimer(TRAFFIC_0_TIMER, red_dur);
				red_state[0] = LED_ON;
				amber_state[0] = LED_OFF;
				green_state[0] = LED_OFF;
			}
			break;
		case AUTO_GREEN:
			if (timer_timeout(TRAFFIC_0_TIMER))
			{
				trafficState[0] = AUTO_AMBER;
				setTimer(TRAFFIC_0_TIMER, amber_dur);
				red_state[0] = LED_OFF;
				amber_state[0] = LED_ON;
				green_state[0] = LED_OFF;
			}
			break;
		}
		UPDATE_RED_LED(0, red_state[0]);
		UPDATE_AMBER_LED(0, amber_state[0]);
		UPDATE_GREEN_LED(0, green_state[0]);
		switch (trafficState[1])
		{
		case INIT:
				trafficState[1] = AUTO_GREEN;
				setTimer(TRAFFIC_1_TIMER, green_dur);
				red_state[1] = LED_OFF;
				amber_state[1] = LED_OFF;
				green_state[1] = LED_ON;
			break;
		case AUTO_RED:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[1] = AUTO_GREEN;
				setTimer(TRAFFIC_1_TIMER, green_dur);
				red_state[1] = LED_OFF;
				amber_state[1] = LED_OFF;
				green_state[1] = LED_ON;
			}
			break;
		case AUTO_AMBER:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[1] = AUTO_RED;
				setTimer(TRAFFIC_1_TIMER, red_dur);
				red_state[1] = LED_ON;
				amber_state[1] = LED_OFF;
				green_state[1] = LED_OFF;
			}
			break;
		case AUTO_GREEN:
			if (timer_timeout(TRAFFIC_1_TIMER))
			{
				trafficState[1] = AUTO_AMBER;
				setTimer(TRAFFIC_1_TIMER, amber_dur);
				red_state[1] = LED_OFF;
				amber_state[1] = LED_ON;
				green_state[1] = LED_OFF;
			}
			break;
		}
		UPDATE_RED_LED(1, red_state[1]);
		UPDATE_AMBER_LED(1, amber_state[1]);
		UPDATE_GREEN_LED(1, green_state[1]);

		if (timer_timeout(SCANNING_TIMER))
		{
			updateLedBuffer(0, timer_remaining(TRAFFIC_0_TIMER));
			updateLedBuffer(1, timer_remaining(TRAFFIC_1_TIMER));
			if (index_led > 3) index_led = 0;
			update7SEG(index_led++);
			setTimer(SCANNING_TIMER, 250);
		}
		break;
	case MODE_2:
		//button_reset(BUTTON1);
		if (isButtonPressed(BUTTON1))
		{
			mode_3_state = 0;
			mode = MODE_3;
		}
		switch (mode_2_state) {
			case 0:
				mode_2_state = 1;
				setTimer(BLINKING_TIMER, 250);
				setTimer(SCANNING_TIMER, 10);
				index_led = 0;
				UPDATE_RED_LED(0, LED_ON);
				UPDATE_AMBER_LED(0, LED_OFF);
				UPDATE_GREEN_LED(0, LED_OFF);
				UPDATE_RED_LED(1, LED_ON);
				UPDATE_AMBER_LED(1, LED_OFF);
				UPDATE_GREEN_LED(1, LED_OFF);
				break;
			case 1:
				if (timer_timeout(BLINKING_TIMER) == 1)
				{
					setTimer(BLINKING_TIMER, 250);
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
				if (isButtonPressed(BUTTON3)) red_dur = red_dur_input * 1000;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, 250);
					updateLedBuffer(0, 2);
					updateLedBuffer(1, red_dur_input);
					if (index_led > 3) index_led = 0;
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
			mode_4_state = 0;
			mode = MODE_4;
		}
		switch (mode_3_state) {
			case 0:
				mode_3_state = 1;
				setTimer(BLINKING_TIMER, 250);
				setTimer(SCANNING_TIMER, 10);
				index_led = 0;
				UPDATE_RED_LED(0, LED_OFF);
				UPDATE_AMBER_LED(0, LED_ON);
				UPDATE_GREEN_LED(0, LED_OFF);
				UPDATE_RED_LED(1, LED_OFF);
				UPDATE_AMBER_LED(1, LED_ON);
				UPDATE_GREEN_LED(1, LED_OFF);
				break;
			case 1:
				if (timer_timeout(BLINKING_TIMER) == 1)
				{
					setTimer(BLINKING_TIMER, 250);
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
				if (isButtonPressed(BUTTON3)) amber_dur = amber_dur_input * 1000;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, 250);
					updateLedBuffer(0, 3);
					updateLedBuffer(1, amber_dur_input);
					if (index_led > 3) index_led = 0;
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
			case 0:
				mode_4_state = 1;
				setTimer(BLINKING_TIMER, 250);
				setTimer(SCANNING_TIMER, 10);
				index_led = 0;
				UPDATE_RED_LED(0, LED_OFF);
				UPDATE_AMBER_LED(0, LED_OFF);
				UPDATE_GREEN_LED(0, LED_ON);
				UPDATE_RED_LED(1, LED_OFF);
				UPDATE_AMBER_LED(1, LED_OFF);
				UPDATE_GREEN_LED(1, LED_ON);
				break;
			case 1:
				if (timer_timeout(BLINKING_TIMER) == 1)
				{
					setTimer(BLINKING_TIMER, 250);
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
				if (isButtonPressed(BUTTON3)) green_dur = green_dur_input * 1000;
				if (timer_timeout(SCANNING_TIMER))
				{
					setTimer(SCANNING_TIMER, 250);
					updateLedBuffer(0, 4);
					updateLedBuffer(1, green_dur_input);
					if (index_led > 3) index_led = 0;
					update7SEG(index_led++);
				}
				break;
			default:
				break;
		}
		break;
	}
}
