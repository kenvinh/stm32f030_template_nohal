/**
  ******************************************************************************
  * File Name          : usart.c
  * Description        : This file provides code for the configuration
  *                      of USART modules
  ******************************************************************************
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "usart.h"

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
volatile uint32_t g_usart1_current_clock;
volatile uint8_t * g_usart1_receive_ptr;
volatile uint16_t g_usart1_receive_length;
volatile uint8_t * g_usart1_transmit_ptr;
volatile uint16_t g_usart1_transmit_length;

/*******************************************************************************
 * Private and Public functions
*******************************************************************************/

/*******************************************************************************
 * Function name  : USART_Init
 * Interface      : uint8_t USART_Init(void)
 * Description    : Init the USART
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
uint8_t USART_Init(void)
{
    /* 
     * Enable USART Clock Supply 
     */
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    
    /* Ensure USART is off */
    USART_MODULE_DISABLE(USART1);

    /* 
     * Configure the USART 
     */
    /* Configure interrupt */
    NVIC_SetPriority(USART1_IRQn, 0);

    /* Configure parameters */
    USART1->CR1 = USART_CR1_OVERSAMPLING_BY_16 | USART_CR1_WORD_LENGTH_8 | USART_CR1_PARITY_NONE |
                  USART_CR1_TRANSMIT_INTERRUPT_DISABLE | USART_CR1_RECEIVE_OVERRUN_INTERRUPT_ENABLE |
                  USART_CR1_ENABLE_TRANSMIT_RECEIVE;
    USART1->CR2 = USART_CR2_AUTOBAUDRATE_DISABLE | USART_CR2_LSB_FIRST | USART_CR2_SIGNAL_LEVEL_NORMAL | 
                  USART_CR2_TX_RX_PIN_NORMAL | USART_CR2_STOP_BIT_1 | USART_CR2_OPERATE_MODE_ASYNCHRONOUS;

    USART1->CR3 = USART_CR3_OVERRUN_ERROR_INTERRUPT_ENABLE | USART_CR3_THREE_SAMPLE_BIT | USART_CR3_CTS_INTERRUPT_DISABLE |
                  USART_CR3_HARDWARE_CONTROL_NONE | USART_CR3_ERROR_INTERRUPT_DISABLE;
    
    USART1_SET_CLOCK_SOURCE(USART_CLOCK_SOURCE_PCLK);

    USART_SET_BAUDRATE(USART1, 38400);
    
    /* Configure the pin, port: PA9 , PA10 */
    GPIO_MODER_SET_VALUE(GPIOA, GPIO_PIN_09 | GPIO_PIN_10, GPIO_MODER_MODE_ALTERNATE);
    GPIO_OSPEEDR_SET_VALUE(GPIOA, GPIO_PIN_09 | GPIO_PIN_10, GPIO_OSPEER_SPEED_HIGH);
    GPIO_PUPDR_SET_VALUE(GPIOA, GPIO_PIN_09 | GPIO_PIN_10, GPIO_PUPDR_PULL_UP);
    GPIO_AFR_SET_VALUE(GPIOA, GPIO_PIN_09 | GPIO_PIN_10, GPIO_AFR_ALTERNATE_FUNC1);
    
    return 0;
}

void USART1_Start(void)
{
    /* Clear flag, enable interrupt */
    USART_CLEAR_ALL_FLAG(USART1);
    NVIC_EnableIRQ(USART1_IRQn);

    /* Enable USART module */
    USART_MODULE_ENABLE(USART1);
}

void USART1_Stop(void)
{
    /* Stop USART module */
    USART_MODULE_DISABLE(USART1);

    /* Clear flag, disable interrupt */
    NVIC_DisableIRQ(USART1_IRQn);
    USART_CLEAR_ALL_FLAG(USART1);
}

void USART1_Send(uint8_t * transmit_buffer, uint16_t size)
{
    /* Transmit polling method */
    while(size > 0)
    {
        USART1->TDR = *transmit_buffer;
        size--;
        while (USART_IS_TRANSMIT_COMPLETE(USART1) != 1)
        {
            __NOP();
        }
    }
}

void USART1_Receive(uint8_t * rcv_buffer, uint16_t size)
{
    /* Receive using interrupt */
    if (size > 0)
    {
        g_usart1_receive_ptr = rcv_buffer;
        g_usart1_receive_length = size;
    }
}