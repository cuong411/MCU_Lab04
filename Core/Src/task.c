/*
 * task.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Cuong
 */

#include "task.h"

void TaskA()
{
	HAL_GPIO_Toggle(A_GPIO_Port, A_GPIO_Pin);
}

void TaskB()
{
	HAL_GPIO_Toggle(B_GPIO_Port, B_GPIO_Pin);
}

void TaskC()
{
	HAL_GPIO_Toggle(C_GPIO_Port, C_GPIO_Pin);
}

void TaskD()
{
	HAL_GPIO_Toggle(D_GPIO_Port, D_GPIO_Pin);
}

void TaskE()
{
	HAL_GPIO_Toggle(E_GPIO_Port, E_GPIO_Pin);
}
