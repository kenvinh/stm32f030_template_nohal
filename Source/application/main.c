/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "driver_config.h"

#include "usart.h"
#include "core.h"

#include "cmd.h"

int main(void)
{
    DRIVERS_Init();
    
    CMD_Start();

    while (1)
    {
        CMD_PollingProcessing();
    }
}
