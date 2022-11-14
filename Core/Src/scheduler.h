/*
 * scheduler.h
 *
 *  Created on: Nov 9, 2022
 *      Author: PC
 */

#ifndef SRC_SCHEDULER_H_
#define SRC_SCHEDULER_H_

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;

	uint32_t 	TaskID;
}sTasks;

#define SCH_MAX_TASKS	40
#define TIMER_TICK 10

void SCH_Init(void);
void SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint32_t taskID);

#endif /* SRC_SCHEDULER_H_ */
