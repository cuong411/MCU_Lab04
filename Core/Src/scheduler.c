/*
 * scheduler.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Cuong
 */

#include "scheduler.h"

void SCH_Init(void)
{
	// clear all tasks
	unsigned char i;
	for(i = 0; i < SCH_MAX_TASKS; i++)
	{
		SCH_Delete_Task(i);
	}
	//Error_code_G = 0;
	//Timer_init();
	//Watchdog_init();
}

void SCH_Update(void)
{
	unsigned char index;
	for(index = 0; index < SCH_MAX_TASKS; index++)
	{
		// check if a task is in this location
		if(SCH_tasks_G[index].pTask != 0)
		{
			if(SCH_tasks_G[index].Delay == 0)
			{
				// the task is due to run, increase 'RunMe' flag
				SCH_tasks_G[index].RunMe += 1;
				if(SCH_tasks_G[index].Period > 0)
				{
					// schedule periodic task to run again
					SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
				}
			}
			else
			{
				// the task is not ready to run
				SCH_tasks_G[index].Delay -= 1;
			}
		}
	}
}

// this function causes a task (function) to be execute at regular intervals or after a user-defined delay
uint32_t SCH_Add_Task(void (* pFunction)(), unsigned int DELAY, unsigned int PERIOD)
{
	unsigned char index = 0;
	// find a gap in the task array if there is one
	while((SCH_tasks_G[index].pTask != 0) && (index < SCH_MAX_TASKS))
	{
		index += 1;
	}
	// check if the array is full
	if(index == SCH_MAX_TASKS)
	{
		// set global error variable
		//Error_code_G = SCH_ERROR_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	// there a gap available to add a task
	SCH_tasks_G[index].pTask = pFunction;
	SCH_tasks_G[index].Delay = DELAY;
	SCH_tasks_G[index].Period = PERIOD;
	SCH_tasks_G[index].RunMe = 0;
	//SCH_tasks_G[index].TaskID = index;
	// return the location of the added task
	return index;
}

void SCH_Dispatch_Tasks(void)
{
	unsigned char index;
	// run the next task if it is ready
	for(index = 0; index < SCH_MAX_TASKS; index++)
	{
		if(SCH_tasks_G[index].RunMe > 0)
		{
			// run the task
			(* SCH_tasks_G[index].pTask)();
			// reset the run flag
			SCH_tasks_G[index].RunMe -= 1;
			// if this is a 'one shot' task, remove it
			if(SCH_tasks_G[index].Period == 0)
			{
				SCH_Delete_Task(index);
			}
		}
	}
	// report the system status, scheduler enters idle mode
	//SCH_Report_status();
	//SCH_Go_To_Sleep();
}

uint8_t SCH_Delete_Task(const tByte TASK_INDEX)
{
	unsigned char Return_code;
	if(SCH_tasks_G[TASK_INDEX].pTask == 0)
	{
		// no task detected
		//Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	}
	else
	{
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code;
}

void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
	// only apply if we report error
	// check for new error code
	if(Error_code_G != Last_error_code_G)
	{
		Error_port = 255 - Error_code_G;
		Last_error_code_G = Error_code_G;
		if(Error_code_G != 0)
		{
			Error_tick_count_G = 60000;
		}
		else
		{
			Error_tick_count_G = 0;
		}
	}
	else
	{
		if(Error_tick_count_G == 0)
		{
			if(--Error_tick_count_G == 0)
			{
				// reset error code
				Error_code_G = 0;
			}
		}
	}
#endif
}
