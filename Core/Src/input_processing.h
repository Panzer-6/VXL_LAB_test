/*
 * input_processing.h
 *
 *  Created on: Oct 27, 2022
 *      Author: PC
 */

#ifndef SRC_INPUT_PROCESSING_H_
#define SRC_INPUT_PROCESSING_H_

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(int timer, int duration);
void fsm_for_input_processing(void);

#endif /* SRC_INPUT_PROCESSING_H_ */
