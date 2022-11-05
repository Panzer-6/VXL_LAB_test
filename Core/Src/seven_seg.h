/*
 * seven_seg.h
 *
 *  Created on: Nov 4, 2022
 *      Author: PC
 */

#ifndef SRC_SEVEN_SEG_H_
#define SRC_SEVEN_SEG_H_

#define MAX_LED 4

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(int timer, int duration);

#endif /* SRC_SEVEN_SEG_H_ */
