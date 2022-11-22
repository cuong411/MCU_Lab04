/*
 * button.c
 *
 *  Created on: Nov 22, 2022
 *      Author: Cuong
 */

#include "button.h"

int button_flag = 0;

int button_counter = 0;

void getKeyInput()
{
    if(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_RESET)
    {
        button_counter++;
        if(button_counter == 5)
        {
            button_flag = 1;
        }
    }
    else
    {
        button_counter = 0;
    }
}
