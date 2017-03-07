/**
  ******************************************************************************
  * File Name          : core_interrupt.c
  * Description        : This file provides code for the interrupt handler of 
  *                      Cortex M core
  ******************************************************************************
  *
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "core.h"
#include "gpio.h"

/*******************************************************************************
 * Macro definition
*******************************************************************************/

/*******************************************************************************
 * Type definition
*******************************************************************************/

/*******************************************************************************
 * Import variables
*******************************************************************************/

/*******************************************************************************
 * Export variables
*******************************************************************************/

/*******************************************************************************
 * Private and Public functions
*******************************************************************************/
extern volatile uint32_t g_core_tick;

void CORE_SysTick_Callback(void);

/*******************************************************************************
 * Function name  : NMI_Handler
 * Interface      : void NMI_Handler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
 * Function name  : HardFault_Handler
 * Interface      : void HardFault_Handler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/*******************************************************************************
 * Function name  : SVC_Handler
 * Interface      : void SVC_Handler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
 * Function name  : PendSV_Handler
 * Interface      : void PendSV_Handler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
 * Function name  : SysTick_Handler
 * Interface      : void SysTick_Handler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void SysTick_Handler(void)
{
    g_core_tick++;

    /* User Callback funtions */
    CORE_SysTick_Callback();
}

/*******************************************************************************
 * Function name  : CORE_SysTick_Callback
 * Interface      : void CORE_SysTick_Callback(void)
 * Description    : Systick user callback function
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_SysTick_Callback(void)
{
    /* Place application code here */
    static uint32_t count = 0;
    count++;
    if (count > 1000)
    {
        count = 0;
        PLATFORM_LED_OUT_PORT->ODR ^= PLATFORM_LED_OUT_PIN;
    }
}