/**
  ******************************************************************************
  * File Name          : cmd.h
  * Description        : Terminal debug command application  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMD_H
#define __CMD_H

/*******************************************************************************
 * Includes
*******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * Macro definition
*******************************************************************************/

/*******************************************************************************
 * Type definition
*******************************************************************************/

/*******************************************************************************
 * Export variables
*******************************************************************************/
extern const uint8_t g_cmd_header[];
extern const uint8_t g_cmd_line_break[];

/*******************************************************************************
 * Macro function
*******************************************************************************/
#define CMD_DRIVER_SEND(buffer,length)                         (USART1_Send(buffer,length))
#define CMD_DRIVER_RECEIVE(buffer,length)                      (USART1_Receive(buffer,length))

#define CMD_DRIVER_START()                                     (USART1_Start())
#define CMD_DRIVER_STOP()                                      (USART1_Stop())

/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
void CMD_Start(void);
void CMD_SendString(uint8_t * ptr_buffer);
void CMD_SendHeader(void);
void CMD_SendLineBreak(void);

void CMD_ReceiveCallBack(void);
void CMD_Printf(const uint8_t *format,...);
void CMD_PollingProcessing(void);

#endif /*__CMD_H */
