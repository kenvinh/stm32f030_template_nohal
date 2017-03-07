/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
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

/*******************************************************************************
 * Function name  : GPIO_Init
 * Interface      : uint8_t GPIO_Init(void)
 * Description    : Init the GPIO
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
uint8_t GPIO_Init(void)
{
    /* Enable GPIO Port Clock Supply */
    SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN | 
                        RCC_AHBENR_GPIOBEN | 
                        RCC_AHBENR_GPIOFEN);

    /* 
     * GPIOA 
     */
    /* Mode */
    GPIO_MODER_SET_VALUE(GPIOA, GPIO_PIN_00 | GPIO_PIN_01 | GPIO_PIN_02 | GPIO_PIN_03 | GPIO_PIN_05 | GPIO_PIN_07, GPIO_MODER_MODE_ANALOG);
    GPIO_MODER_SET_VALUE(GPIOA, GPIO_PIN_04, GPIO_MODER_MODE_OUTPUT);
    
    /* Type */
    GPIO_OTYPER_SET_VALUE(GPIOA, GPIO_PIN_04, GPIO_OTYPER_OUTPUT_PUSHPULL);

    /* Speed */
    GPIO_OSPEEDR_SET_VALUE(GPIOA, GPIO_PIN_04, GPIO_OSPEER_SPEED_MEDIUM);

    /* Pull */
    GPIO_PUPDR_SET_VALUE(GPIOA, GPIO_PIN_04, GPIO_PUPDR_PULL_NONE);
    
    /*
     * GPIOB
     */
    /* Mode */
    GPIO_MODER_SET_VALUE(GPIOB, GPIO_PIN_01, GPIO_MODER_MODE_ANALOG);

    return 0;
}
