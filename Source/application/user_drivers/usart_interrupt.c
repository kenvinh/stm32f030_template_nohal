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
#include "usart.h"

/* User application */
#include "cmd.h"

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
void USART1_ReceiveEnd_Callback(void);
void USART1_TransmitEnd_Callback(void);

/*******************************************************************************
 * Function name  : USART1_IRQHandler
 * Interface      : void USART1_IRQHandler(void)
 * Description    : Symbol in interrupt vector table
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
    uint32_t error;
    uint8_t rx_data;

    error = USART_GET_ERROR_CODE(USART1);
    
    /* Check for error status in hardware */
    if (error)
    {
        /* Process the error : bypass */
        USART1->ICR = error;
    }
    
    /* Is Receive interrupt */
    if (USART_IS_DATA_RECEIVED(USART1))
    {
        /* Read data to clear flag */
        rx_data = USART1->RDR;

        /* User Callback function */
        if (g_usart1_receive_length > 0)
        {
            *g_usart1_receive_ptr = rx_data;
            g_usart1_receive_ptr++;
            g_usart1_receive_length--;
            if (g_usart1_receive_length == 0)
            {
                USART1_ReceiveEnd_Callback();
            }
        }
    }

    if (USART_IS_TRANSMIT_COMPLETE(USART1))
    {
        USART_TRANSMIT_COMPLETE_FLAG_CLEAR(USART1);
        
        /* User Callback function */
        if (g_usart1_transmit_length > 0)
        {
            USART1->TDR = *g_usart1_transmit_ptr;
            g_usart1_transmit_length--;
            g_usart1_transmit_ptr++;
        }
        else
        {
            USART1_TransmitEnd_Callback();
        }
    }
}

/*******************************************************************************
 * Function name  : USART1_ReceiveEnd_Callback
 * Interface      : void USART1_ReceiveEnd_Callback(void)
 * Description    : USART1 Receive End Call Back
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void USART1_ReceiveEnd_Callback(void)
{
    /* Place application code here */
    CMD_ReceiveCallBack();

}

/*******************************************************************************
 * Function name  : USART1_TransmitEnd_Callback
 * Interface      : void USART1_TransmitEnd_Callback(void)
 * Description    : USART1 Transmit End Call Back
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void USART1_TransmitEnd_Callback(void)
{
    /* Place application code here */
}