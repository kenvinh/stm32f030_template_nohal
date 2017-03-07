/**
  ******************************************************************************
  * File Name          : rcc.c
  * Description        : This file provides code for the configuration
  *                      of system clock
  ******************************************************************************
  *
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "rcc.h"
#include "core.h"
#include "system_stm32f0xx.h"

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
volatile RCC_INFO g_rcc_info;

/*******************************************************************************
 * Private and Public functions
*******************************************************************************/
static void RCC_UpdateClockValue(void);

/*******************************************************************************
 * Function name  : RCC_Init
 * Interface      : uint8_t RCC_Init(void)
 * Description    : Init the System clock
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
uint8_t RCC_Init(void)
{
    uint32_t tmp;

    /* Fill unused clock */
    g_rcc_info.current_rtcclk = 0;
    g_rcc_info.current_rtcclk_source = RTCCLK_SRC_NONE;
    g_rcc_info.input_lseclk = SYSTEM_INPUT_LSE_CLOCK;
    
    /*!<Configure oscillator 
    */
    
    g_rcc_info.input_hseclk = SYSTEM_INPUT_HSE_CLOCK;
    /* Turn on HSE */
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    /* Wait until HSE stable */
    CORE_SysTick_ResetTick();
    while (RCC_IS_HSE_READY() != 1)
    {
        if (CORE_SysTick_GetTick() >= HSE_TIMEOUT_VALUE)
        {
            return 1;
        }
    }

    /*!<Configure clock source 
    */
    /* Configure Flash latency according to setting clock of HCLK 
     * 0     < HCLK <= 24MHz 0
     * 24MHz < HCLK <= 48MHz 1
     * Current peripheral definition not have latency definition, only 0 or 1
    */
    tmp = 0;

    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, tmp);

    /* Confirm flash latency setting */
    if (FLASH->ACR & FLASH_ACR_LATENCY != tmp)
    {
        return 1;
    }

    /* Configure SYSCLK source 
     * Using HSE
    */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSE);
    
    /* Configure HCLK */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);

    /* Configure APB1 Clock */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, RCC_CFGR_PPRE_DIV1);

    /* Update system clock value */
    RCC_UpdateClockValue();

    /*!<Configure SysTick*/
    /* Default use HCLK/1 for SysTick */
    SET_BIT(SysTick->CTRL, SYSTICK_CLKSRC_HCLK); 
    SysTick_Config(g_rcc_info.current_hclk / 1000);
    NVIC_SetPriority(SysTick_IRQn, 15);

    return 0;
}

void RCC_UpdateClockValue(void)
{
    uint32_t tmp, pllmul, plldiv, pllsource;
    
    /* Update the SYSCLK */
    tmp = RCC->CFGR & RCC_CFGR_SWS;
    
    switch (tmp)
    {
        case RCC_CFGR_SWS_HSE:
            g_rcc_info.current_sysclk_source = SYSCLK_SRC_HSE;
            g_rcc_info.current_sysclk = SYSTEM_INPUT_HSE_CLOCK;
            break;
        case RCC_CFGR_SWS_PLL:
            g_rcc_info.current_sysclk_source = SYSCLK_SRC_PLL;
            /* Get PLL clock source and multiplication factor ----------------------*/
            pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmul = ((RCC->CFGR & RCC_CFGR_PLLMUL)>> 18 + 2);
            plldiv = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

            if (pllsource == RCC_CFGR_PLLSRC_HSI_DIV2)
            {
                /* HSI oscillator clock divided by 2 selected as PLL clock entry */
                g_rcc_info.current_sysclk = (RCC_DEFAULT_HSI_CLOCK_MHZ >> 1) * pllmul;
            }
            else
            {
                /* HSE selected as PLL clock entry */
                g_rcc_info.current_sysclk = (SYSTEM_INPUT_HSE_CLOCK / plldiv) * pllmul;
            }
            break;
        case RCC_CFGR_SWS_HSI:
        default:
            g_rcc_info.current_sysclk_source = SYSCLK_SRC_HSI;
            g_rcc_info.current_sysclk = RCC_DEFAULT_HSI_CLOCK_MHZ;
            break;
    }

    /* Update the HCLK (AHB clock) */
    tmp = AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];
    g_rcc_info.current_hclk = g_rcc_info.current_sysclk >> tmp;

    /* Update the APB1 clock */
    tmp = APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE) >> RCC_CFGR_PPRE_Pos];
    g_rcc_info.current_apb1clk = g_rcc_info.current_sysclk >> tmp;

}