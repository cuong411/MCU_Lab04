/*
 * task.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Cuong
 */

#include "task.h"

void TaskA()
{
	HAL_GPIO_TogglePin(A_GPIO_Port, A_Pin);
}

void TaskB()
{
	HAL_GPIO_TogglePin(B_GPIO_Port, B_Pin);
}

void TaskC()
{
	HAL_GPIO_TogglePin(C_GPIO_Port, C_Pin);
}

void TaskD()
{
	HAL_GPIO_TogglePin(D_GPIO_Port, D_Pin);
}

void TaskE()
{
	if(button_flag == 1)
	{
		button_flag = 0;
		HAL_GPIO_TogglePin(E_GPIO_Port, E_Pin);
	}
}
