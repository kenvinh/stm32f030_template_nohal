/**
  ******************************************************************************
  * File Name          : core.c
  * Description        : This file provides code for the configuration
  *                      of MCU core
  ******************************************************************************
  *
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "core.h"
#include "rcc.h"

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
volatile uint32_t g_core_tick = 0;

/*******************************************************************************
 * Function name  : CORE_Init
 * Interface      : uint8_t CORE_Init(void)
 * Description    : Init the Cortex Core
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
uint8_t CORE_Init(void)
{
     /* Core initialization
      * Flash configuration: Prefetch or not only, default is using prefetch
      * NVIC Priority Grouping: rule (no using subpriority)
      * SysTick: configure for operation with HSI first, will edit one more time when set clock
      */
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
    
    /* After reset using HSI 8MHz */
    SysTick_Config(RCC_DEFAULT_HSI_CLOCK_MHZ / 1000);

    return 0;
}

/*******************************************************************************
 * Function name  : CORE_Delay
 * Interface      : void CORE_Delay(uint16_t us)
 * Description    : Short software delay using instruction
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_Delay(uint16_t us)
{
    switch(RCC_GET_CURRENT_HCLK())
    {
        case 8000000:
        default:
            break;
    }
}

/*******************************************************************************
 * Function name  : CORE_SysTick_Delay
 * Interface      : void CORE_SysTick_Delay(uint32_t ms)
 * Description    : Ms delay by waiting for number of tick
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_SysTick_Delay(uint32_t ms)
{
    CORE_SysTick_HaltTick();

    g_core_tick = 0;

    CORE_SysTick_ResumeTick();

    while (g_core_tick < ms)
    {
        __NOP();
    }
}

/*******************************************************************************
 * Function name  : CORE_SysTick_GetTick
 * Interface      : uint32_t CORE_SysTick_GetTick(void)
 * Description    : Get current tick counter value
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
uint32_t CORE_SysTick_GetTick(void)
{
    return g_core_tick;
}

/*******************************************************************************
 * Function name  : CORE_SysTick_ResetTick
 * Interface      : void CORE_SysTick_ResetTick(void)
 * Description    : Reset the tick counter
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_SysTick_ResetTick(void)
{
    /* Stop tick before reset */
    CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
    g_core_tick = 0;
    /* Resume the tick */
    SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/*******************************************************************************
 * Function name  : CORE_SysTick_HaltTick
 * Interface      : void CORE_SysTick_HaltTick(void)
 * Description    : Halt the tick counter
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_SysTick_HaltTick(void)
{
    /* Disable SysTick Interrupt */
    CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}

/*******************************************************************************
 * Function name  : CORE_SysTick_ResumeTick
 * Interface      : void CORE_SysTick_ResumeTick(void)
 * Description    : Resume the tick counter
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CORE_SysTick_ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);
}
