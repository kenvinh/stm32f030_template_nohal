/**
  ******************************************************************************
  * File Name          : usart.h
  * Description        : This file contains all the functions prototypes for 
  *                      the USART module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "stm32f0xx.h"
#include "driver_config.h"

/* Other modules */
#include "rcc.h"
#include "gpio.h"

/*******************************************************************************
 * Macro definition
*******************************************************************************/
/*
 * USARTx->CR1 register
*/
#define USART_CR1_WORD_LENGTH_8                         (uint32_t)(0x00000000)
#define USART_CR1_WORD_LENGTH_9                         (USART_CR1_M)

#define USART_CR1_END_BLOCK_INTERRUPT_DISABLE           (uint32_t)(0x00000000)
#define USART_CR1_END_BLOCK_INTERRUPT_ENABLE            (USART_CR1_EOBIE)

#define USART_CR1_RCV_TIMEOUT_INTERRUPT_DISABLE         (uint32_t)(0x00000000)
#define USART_CR1_RCV_TIMEOUT_INTERRUPT_ENABLE          (USART_CR1_RTOIE)

#define USART_CR1_RCV_TIMEOUT_INTERRUPT_DISABLE         (uint32_t)(0x00000000)
#define USART_CR1_RCV_TIMEOUT_INTERRUPT_ENABLE          (USART_CR1_RTOIE)

/* Driver Enable definition defined separately */

#define USART_CR1_OVERSAMPLING_BY_16                    (uint32_t)(0x00000000)
#define USART_CR1_OVERSAMPLING_BY_08                    (USART_CR1_OVER8)

#define USART_CR1_CHAR_MATCH_INTERRUPT_DISABLE          (uint32_t)(0x00000000)
#define USART_CR1_CHAR_MATCH_INTERRUPT_ENABLE           (USART_CR1_CMIE)

#define USART_CR1_MUTE_MODE_DISABLE                     (uint32_t)(0x00000000)
#define USART_CR1_MUTE_MODE_ENABLE                      (USART_CR1_MME)

#define USART_CR1_RECEIVER_WAKE_UP_IDLE_LINE            (uint32_t)(0x00000000)
#define USART_CR1_RECEIVER_WAKE_UP_ADDR_MARK            (USART_CR1_WAKE)

#define USART_CR1_PARITY_NONE                           (uint32_t)(0x00000000)
#define USART_CR1_PARITY_EVEN                           (USART_CR1_PCE)
#define USART_CR1_PARITY_ODD                            (USART_CR1_PCE | USART_CR1_PS)

#define USART_CR1_PARITY_ERROR_INTERRUPT_DISABLE        (uint32_t)(0x00000000)
#define USART_PARITY_ERROR_INTERRUPT_ENABLE             (USART_CR1_PEIE)

#define USART_CR1_TRANSMIT_INTERRUPT_DISABLE            (uint32_t)(0x00000000)
#define USART_CR1_TRANSMIT_EMPTY_INTERRUPT_ENABLE       (USART_CR1_TXEIE)
#define USART_CR1_TRANSMIT_COMPLETE_INTERRUPT_ENABLE    (USART_CR1_TCIE)

#define USART_CR1_RECEIVE_OVERRUN_INTERRUPT_DISABLE     (uint32_t)(0x00000000)
#define USART_CR1_RECEIVE_OVERRUN_INTERRUPT_ENABLE      (USART_CR1_RXNEIE)

#define USART_CR1_IDLE_INTERRUPT_DISABLE                (uint32_t)(0x00000000)
#define USART_CR1_IDLE_INTERRUPT_ENABLE                 (USART_CR1_IDLEIE)

#define USART_CR1_ENABLE_TRANSMIT_ONLY                  (USART_CR1_TE)
#define USART_CR1_ENABLE_RECEIVE_ONLY                   (USART_CR1_RE)
#define USART_CR1_ENABLE_TRANSMIT_RECEIVE               (USART_CR1_TE | USART_CR1_RE)

/*
 * USARTx->CR2 register
*/

/* Receive timeout enable and register will be define in function */
#define USART_CR2_AUTOBAUDRATE_DISABLE                  (uint32_t)(0x00000000)
#define USART_CR2_AUTOBAUDRATE_MODE_START_BIT           (USART_CR2_ABREN)
#define USART_CR2_AUTOBAUDRATE_MODE_FALLING_EDGE        (USART_CR2_ABREN | USART_CR2_ABRMODE_0)
#define USART_CR2_AUTOBAUDRATE_MODE_FRAME_7FH           (USART_CR2_ABREN | USART_CR2_ABRMODE_1)
#define USART_CR2_AUTOBAUDRATE_MODE_FRAME_55H           (USART_CR2_ABREN | USART_CR2_ABRMODE)

#define USART_CR2_LSB_FIRST                             (uint32_t)(0x00000000)
#define USART_CR2_MSB_FIRST                             (USART_CR2_MSBFIRST)

#define USART_CR2_SIGNAL_LEVEL_NORMAL                   (uint32_t)(0x00000000)
#define USART_CR2_SIGNAL_LEVEL_INVERSION                (USART_CR2_DATAINV | USART_CR2_TXINV | USART_CR2_RXINV)

#define USART_CR2_TX_RX_PIN_NORMAL                      (uint32_t)(0x00000000)
#define USART_CR2_TX_RX_PIN_SWAP                        (USART_CR2_SWAP)

#define USART_CR2_STOP_BIT_1                            (uint32_t)(0x00000000)
#define USART_CR2_STOP_BIT_2                            (USART_CR2_STOP_1)

#define USART_CR2_OPERATE_MODE_ASYNCHRONOUS             (uint32_t)(0x00000000)
#define USART_CR2_OPERATE_MODE_SYNCHRONOUS              (USART_CR2_CLKEN)

/* Synchronous */
#define USART_CR2_SYNC_CLK_LOW_SAMPLE_RISING            (uint32_t)(0x00000000)              /*!<Clock line idle state low, sample on rising edge */
#define USART_CR2_SYNC_CLK_LOW_SAMPLE_FALLING           (USART_CR2_CPHA)                    /*!<Clock line idle state low, sample on falling edge */
#define USART_CR2_SYNC_CLK_HIGH_SAMPLE_FALLING          (USART_CR2_CPOL)                    /*!<Clock line idle state high, sample on falling edge */
#define USART_CR2_SYNC_CLK_HIGH_SAMPLE_RISING           (USART_CR2_CPOL | USART_CR2_CPHA)   /*!<Clock line idle state high, sample on rising edge */

/* Synchronous */
#define USART_CR2_SYNC_LAST_BIT_CLOCK_DISABLE           (uint32_t)(0x00000000)
#define USART_CR2_SYNC_LAST_BIT_CLOCK_ENABLE            (USART_CR2_LBCL)

/*
 * USARTx->CR3 register
*/
#define USART_CR3_DMA_DISABLE_ON_ERROR                  (USART_CR3_DDRE)
#define USART_CR3_DMA_CONTINUE_ON_ERROR                 (uint32_t)(0x00000000)

#define USART_CR3_OVERRUN_ERROR_INTERRUPT_DISABLE       (USART_CR3_OVRDIS)
#define USART_CR3_OVERRUN_ERROR_INTERRUPT_ENABLE        (uint32_t)(0x00000000)

#define USART_CR3_THREE_SAMPLE_BIT                      (uint32_t)(0x00000000)
#define USART_CR3_ONE_SAMPLE_BIT                        (USART_CR3_ONEBIT)

#define USART_CR3_CTS_INTERRUPT_DISABLE                 (uint32_t)(0x00000000)
#define USART_CR3_CTS_INTERRUPT_ENABLE                  (USART_CR3_CTSIE)

#define USART_CR3_HARDWARE_CONTROL_NONE                 (uint32_t)(0x00000000)
#define USART_CR3_HARDWARE_CONTROL_CTS                  (USART_CR3_CTSE)
#define USART_CR3_HARDWARE_CONTROL_RTS                  (USART_CR3_RTSE)
#define USART_CR3_HARDWARE_CONTROL_CTS_RTS              (USART_CR3_CTSE | USART_CR3_RTSE)

#define USART_CR3_DMA_NONE                              (uint32_t)(0x00000000)
#define USART_CR3_DMA_TRANSMITTER                       (USART_CR3_DMAT)
#define USART_CR3_DMA_RECEIVER                          (USART_CR3_DMAR)
#define USART_CR3_DMA_TRANSMITTER_RECEIVER              (USART_CR3_DMAT | USART_CR3_DMAR)

/* Synchronous */
#define USART_CR3_HALF_DUPLEX_NONE                      (uint32_t)(0x00000000)
#define USART_CR3_HALF_DUPLEX_SELECTED                  (USART_CR3_HDSEL)

#define USART_CR3_ERROR_INTERRUPT_DISABLE               (uint32_t)(0x00000000)
#define USART_CR3_ERROR_INTERRUPT_ENABLE                (USART_CR3_EIE)         /*!<FE and NF (this bit or RXNEIE set will enable ORE)*/

/*******************************************************************************
 * Type definition
*******************************************************************************/
typedef enum 
{
    USART_CLOCK_SOURCE_PCLK = RCC_CFGR3_USART1SW_PCLK,
    USART_CLOCK_SOURCE_SYSCLK = RCC_CFGR3_USART1SW_SYSCLK,
    USART_CLOCK_SOURCE_LSE = RCC_CFGR3_USART1SW_LSE,
    USART_CLOCK_SOURCE_HSI = RCC_CFGR3_USART1SW_HSI,
} USART_Clock_Source_t;

/*******************************************************************************
 * Export variables
*******************************************************************************/
extern volatile uint32_t g_usart1_current_clock;
extern volatile uint8_t * g_usart1_receive_ptr;
extern volatile uint16_t g_usart1_receive_length;
extern volatile uint8_t * g_usart1_transmit_ptr;
extern volatile uint16_t g_usart1_transmit_length;

/*******************************************************************************
 * Macro function
*******************************************************************************/
#define USART_MODULE_DISABLE(usart)                     (usart->CR1 &= ~USART_CR1_UE)
#define USART_MODULE_ENABLE(usart)                      (usart->CR1 |= USART_CR1_UE)

/* Set the USART1 clock source: from USART_Clock_Source_t */
#define USART1_SET_CLOCK_SOURCE(source)                 {\
                                                            MODIFY_REG(RCC->CFGR3, RCC_CFGR3_USART1SW, source);\
                                                            switch(source)\
                                                            {\
                                                                case USART_CLOCK_SOURCE_PCLK:\
                                                                    g_usart1_current_clock = RCC_GET_CURRENT_APB1CLK();\
                                                                    break;\
                                                                case USART_CLOCK_SOURCE_SYSCLK:\
                                                                    g_usart1_current_clock = RCC_GET_CURRENT_SYSCLK();\
                                                                    break;\
                                                                case USART_CLOCK_SOURCE_LSE:\
                                                                    g_usart1_current_clock = RCC_GET_INPUT_LSE_CLK();\
                                                                    break;\
                                                                case USART_CLOCK_SOURCE_HSI:\
                                                                    g_usart1_current_clock = RCC_GET_HSI_CLK();\
                                                                    break;\
                                                                default:\
                                                                    g_usart1_current_clock = RCC_GET_CURRENT_APB1CLK();\
                                                                    break;\
                                                            }\
                                                        }

#define USART_SET_BAUDRATE(usart,rate)                  {\
                                                            uint32_t tmp;\
                                                            tmp = (g_usart1_current_clock / rate);\
                                                            if (usart->CR1 & USART_CR1_OVER8)\
                                                            {\
                                                                tmp = (tmp & (~USART_BRR_DIV_FRACTION)) | ((tmp & USART_BRR_DIV_FRACTION) >> 1);\
                                                                usart->BRR = tmp;\
                                                            }\
                                                            else\
                                                            {\
                                                                usart->BRR = tmp;\
                                                            }\
                                                        }

/* Is there any error */
#define USART_GET_ERROR_CODE(usart)                     (usart->ISR & (USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE))

#define USART_IS_TRANSMIT_COMPLETE(usart)               (((usart->ISR & USART_ISR_TC) != 0) ? 1 : 0)
#define USART_IS_DATA_RECEIVED(usart)                   (((usart->ISR & USART_ISR_RXNE) != 0) ? 1 : 0)

/* Flag clear */
#define USART_RECEIVE_FLUSH_BUFFER(usart)               (usart->RQR = USART_RQR_RXFRQ)
#define USART_TRANSMIT_COMPLETE_FLAG_CLEAR(usart)       (usart->ICR = USART_ICR_TCCF)
#define USART_CLEAR_ALL_FLAG(usart)                     {\
                                                            USART_RECEIVE_FLUSH_BUFFER(usart);\
                                                            usart->ICR = USART_ICR_CMCF | USART_ICR_RTOCF | USART_ICR_CTSCF | \
                                                                         USART_ICR_TCCF | USART_ICR_IDLECF | USART_ICR_ORECF | \
                                                                         USART_ICR_NCF | USART_ICR_FECF | USART_ICR_PECF;\
                                                        }

/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
uint8_t USART_Init(void);
void USART1_Start(void);
void USART1_Stop(void);
void USART1_Send(uint8_t * transmit_buffer, uint16_t size);
void USART1_Receive(uint8_t * rcv_buffer, uint16_t size);

#endif /* __USART_H */