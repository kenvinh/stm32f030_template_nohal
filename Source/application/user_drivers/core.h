/**
  ******************************************************************************
  * File Name          : core.h
  * Description        : This file contains all the functions prototypes for 
  *                      the cortex core  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORE_H
#define __CORE_H

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "stm32f0xx.h"
#include "driver_config.h"

/*******************************************************************************
 * Macro definition
*******************************************************************************/
/* NVIC Grouping */
#define NVIC_PRIORBIT_GROUP0_SUB4 ((uint32_t)0x00000007) /*!< 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PRIORBIT_GROUP1_SUB3 ((uint32_t)0x00000006) /*!< 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PRIORBIT_GROUP2_SUB2 ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PRIORBIT_GROUP3_SUB1 ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PRIORBIT_GROUP4_SUB0 ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority 0 bits for subpriority */

/* SysTick Configuration */
#define SYSTICK_CLKSRC_HCLK_DIV8  ((uint32_t)0x00000000)
#define SYSTICK_CLKSRC_HCLK       ((uint32_t)0x00000004)

/*******************************************************************************
 * Type definition
*******************************************************************************/

/*******************************************************************************
 * Export variables
*******************************************************************************/

/*******************************************************************************
 * Macro function
*******************************************************************************/

/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
uint8_t CORE_Init(void);
void CORE_Delay(uint16_t us);


void CORE_SysTick_Delay(uint32_t ms);
uint32_t CORE_SysTick_GetTick(void);
void CORE_SysTick_ResetTick(void);
void CORE_SysTick_HaltTick(void);
void CORE_SysTick_ResumeTick(void);
#endif /* __CORE_H */