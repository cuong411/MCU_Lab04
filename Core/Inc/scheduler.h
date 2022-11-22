/*
 * scheduler.h
 *
 *  Created on: Nov 22, 2022
 *      Author: Cuong
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "global.h"
#include "main.h"
#include "task.h"

typedef struct sTask
{
	// pointer to the task
	void (* pTask) (void);
	// delay until the function return
	uint32_t Delay;
	// interval between subsequent runs
	uint32_t Period;
	// incremented by scheduler when task is due to run
	uint8_t RunMe;
	// used to allocate where to delete task
	uint32_t TaskID;
};

#define SCH_MAX_TASKS	40
#define NO_TASK_ID		0
struct sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void (* pFunction)(), unsigned int DELAY, unsigned int PERIOD);
uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX);
//void SCH_Report_Status(void);
//void SCH_Go_To_Sleep();

#endif /* INC_SCHEDULER_H_ */
