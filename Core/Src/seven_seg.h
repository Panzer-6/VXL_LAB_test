/*
 * seven_seg.h
 *
 *  Created on: Nov 6, 2022
 *      Author: PC
 */

#ifndef SRC_SEVEN_SEG_H_
#define SRC_SEVEN_SEG_H_

#define MAX_LED 4

enum SEVEN_SEG_CONFIG {SEVEN_SEG_PAIR_1_2, SEVEN_SEG_PAIR_3_4};
extern enum SEVEN_SEG_CONFIG seven_seg_config;

extern int index_led;

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(int config, int value);

#endif /* SRC_SEVEN_SEG_H_ */
