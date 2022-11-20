/*
 * scheduler.c
 *
 *  Created on: Nov 9, 2022
 *      Author: PC
 */

#include <stdint.h>
#include "task.h"
#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
sTasks recentTask;
uint8_t current_index_task = 0;
uint32_t recentDelay = 0;

void swap(sTasks* item1, sTasks* item2)
{
	sTasks temp = *item1;
	*item1 = *item2;
	*item2 = temp;
}

void sortTask()
{
	for (int i = current_index_task; i > 0; i--)
	{
		while (SCH_tasks_G[i].Delay < SCH_tasks_G[i - 1].Delay)
		{
			swap(&SCH_tasks_G[i - 1], &SCH_tasks_G[i]);
			i--;
		}
	}
	for (int i = 0; i < current_index_task; i++)
	{
		SCH_tasks_G[i].TaskID = i;
	}
}

void shiftTask(int index)
{
	for (int i = current_index_task - 1; i > index; i--)
	{
		SCH_tasks_G[i] = SCH_tasks_G[i - 1];
	}
	SCH_tasks_G[index].pTask = 0x0000;
	SCH_tasks_G[index].Delay = 0;
	SCH_tasks_G[index].Period =  0;
	SCH_tasks_G[index].RunMe = 0;
	SCH_tasks_G[index].TaskID = 0;
}

sTasks topTask()
{
	return SCH_tasks_G[0];
}

void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		if (current_index_task == 0)
		{
			SCH_tasks_G[0].pTask = pFunction;
			SCH_tasks_G[0].Delay = DELAY / TIMER_TICK;
			SCH_tasks_G[0].Period =  PERIOD / TIMER_TICK;
			SCH_tasks_G[0].RunMe = 0;
			current_index_task++;
		}
		else
		{
			int insert_index = 0;
			sTasks insertTask;
			insertTask.pTask = pFunction;
			insertTask.Delay = DELAY / TIMER_TICK;
			insertTask.Period = PERIOD / TIMER_TICK;
			insertTask.RunMe = 0;
			while (insertTask.Delay > SCH_tasks_G[insert_index].Delay && insert_index < current_index_task)
			{
				insertTask.Delay -= SCH_tasks_G[insert_index].Delay;
				insert_index++;

			}
			current_index_task++;
			shiftTask(insert_index);
			SCH_tasks_G[insert_index] = insertTask;
			SCH_tasks_G[insert_index + 1].Delay -= SCH_tasks_G[insert_index].Delay;
		}
		/*
		else if (())
		int insert_index = 0;
		for (insert_index = 0; insert_index < current_index_task; insert_index++)
		{
			if (SCH_tasks_G[insert_index].Delay > (DELAY / TIMER_TICK)) break;
		}
		current_index_task++;
		shiftTask(insert_index);
		SCH_tasks_G[insert_index].pTask = pFunction;
		SCH_tasks_G[insert_index].Delay = DELAY / TIMER_TICK;
		SCH_tasks_G[insert_index].Period =  PERIOD / TIMER_TICK;
		SCH_tasks_G[insert_index].RunMe = 0;
		for (int i = 0; i < current_index_task; i++)
		{
			SCH_tasks_G[i].TaskID = i;
		}
		*/
	}
}

void SCH_Delete_Task(uint32_t taskID)
{
	if (taskID < current_index_task)
	{
		//free(SCH_tasks_G[].pTask);
		for (int i = taskID; i < current_index_task - 1; i++)
		{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
			SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
			SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
			SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
		}
		SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
		SCH_tasks_G[current_index_task - 1].Delay = 0;
		SCH_tasks_G[current_index_task - 1].Period =  0;
		SCH_tasks_G[current_index_task - 1].RunMe = 0;
		SCH_tasks_G[current_index_task - 1].TaskID = 0;
		current_index_task--;
	}
}

void SCH_Update(void)
{
	/*
	for (int i = 0; i < current_index_task; i++)
	{
		if (SCH_tasks_G[i].pTask != 0x0000)
		{
			if (SCH_tasks_G[i].Delay > 0)
			{
				SCH_tasks_G[i].Delay--;
			}
			else
			{
				SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				SCH_tasks_G[i].RunMe += 1;
			}
		}
	}
*/
	if (SCH_tasks_G[0].Delay > 0)
	{
		SCH_tasks_G[0].Delay--;
	}
	if (SCH_tasks_G[0].Delay == 0) SCH_tasks_G[0].RunMe++;
}

void SCH_Dispatch_Tasks(void){
	/*
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].pTask != 0x0000)
		{
			if(SCH_tasks_G[i].RunMe > 0){
				SCH_tasks_G[i].RunMe--;
				(*SCH_tasks_G[i].pTask)();
				if (SCH_tasks_G[i].Period == 0)
				{
					SCH_Delete_Task(SCH_tasks_G[i].TaskID);
				}
			}
		}
	}
	*/

	while (SCH_tasks_G[0].pTask != 0x0000)
	{
		if (SCH_tasks_G[0].RunMe > 0)
		{
			SCH_tasks_G[0].RunMe--;
			(*SCH_tasks_G[0].pTask)();
			if (SCH_tasks_G[1].Delay == 0) SCH_tasks_G[1].RunMe++;
			if (SCH_tasks_G[0].Period > 0) SCH_Add_Task(SCH_tasks_G[0].pTask, SCH_tasks_G[0].Period * TIMER_TICK, SCH_tasks_G[0].Period * TIMER_TICK);
			SCH_Delete_Task(0);
			recentTask = topTask();
		}
	}
}

void SCH_Init(void)
{
	  SCH_Add_Task(toggleBlueLed, 0, 2000);
	  SCH_Add_Task(toggleRedLed, 0, 500);
	  SCH_Add_Task(toggleOrangeLed, 0, 2500);
	  SCH_Add_Task(toggleYellowLed, 0, 1500);
	  SCH_Add_Task(toggleGreenLed, 0, 1000);
	  recentTask = topTask();
}
