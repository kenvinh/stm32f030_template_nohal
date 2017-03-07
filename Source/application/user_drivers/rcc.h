/**
  ******************************************************************************
  * File Name          : rcc.h
  * Description        : This file contains all the functions prototypes for 
  *                      the system clock
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RCC_H
#define __RCC_H

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "stm32f0xx.h"
#include "driver_config.h"

/*******************************************************************************
 * Macro definition
*******************************************************************************/
#define HSE_TIMEOUT_VALUE               (100)   /*!<100ms*/
#define HSI_TIMEOUT_VALUE               (2)     /*!<2ms*/
#define LSE_TIMEOUT_VALUE               (5000)  /*!<5000ms*/

#define RCC_DEFAULT_HSI_CLOCK_MHZ       (8000000U)    /*!<8Mhz*/

#define RCC_IS_HSE_READY()              ((RCC->CR & RCC_CR_HSERDY) == RCC_CR_HSERDY)
#define RCC_IS_HSI_READY()              ((RCC->CR & RCC_CR_HSIRDY) == RCC_CR_HSIRDY)

/*******************************************************************************
 * Type definition
*******************************************************************************/
typedef enum tagSysclkSource
{
    SYSCLK_SRC_HSI,
    SYSCLK_SRC_HSE,
    SYSCLK_SRC_PLL,
} SYSCLK_SRC_T;

typedef enum tagRtcclkSource
{
    RTCCLK_SRC_NONE,
    RTCCLK_SRC_HSE,
    RTCCLK_SRC_LSE,
    RTCCLK_SRC_LSI,
} RTCCLK_SRC_T;

typedef struct tagRCCInfo
{
    uint32_t current_sysclk;
    uint32_t current_hclk;
    uint32_t current_apb1clk;
    uint32_t current_apb2clk;
    uint32_t current_rtcclk;
    uint32_t input_lseclk;
    uint32_t input_hseclk;
    SYSCLK_SRC_T current_sysclk_source;
    RTCCLK_SRC_T current_rtcclk_source;
} RCC_INFO;


/*******************************************************************************
 * Export variables
*******************************************************************************/
extern volatile RCC_INFO g_rcc_info;

/*******************************************************************************
 * Macro function
*******************************************************************************/
/* Please note, only called these macro after RCC Init */
#define RCC_GET_CURRENT_SYSCLK()            (g_rcc_info.current_sysclk)
#define RCC_GET_CURRENT_HCLK()              (g_rcc_info.current_hclk)
#define RCC_GET_CURRENT_APB1CLK()              (g_rcc_info.current_apb1clk)
#define RCC_GET_INPUT_HSE_CLK()                 (g_rcc_info.input_hseclk)
#define RCC_GET_INPUT_LSE_CLK()                 (g_rcc_info.input_lseclk)
#define RCC_GET_HSI_CLK()                       (RCC_DEFAULT_HSI_CLOCK_MHZ)

/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
uint8_t RCC_Init(void);

#endif /* __RCC_H */