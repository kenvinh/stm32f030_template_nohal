/**
  ******************************************************************************
  * File Name          : cmd.c
  * Description        : Terminal debug command application
  ******************************************************************************
  */

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "cmd.h"
#include "core.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * Macro definition
*******************************************************************************/
#define CMD_PRINTF_BUFFER           (128)
#define CMD_MAX_INPUT_BUFFER        (1)
#define CMD_KEY_ENTER               (0x0D)

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
uint8_t g_cmd_received_byte;
uint8_t g_cmd_is_received;
uint8_t g_cmd_is_cmd_entered;
uint8_t g_cmd_current_index;
uint8_t g_cmd_input_buffer[CMD_MAX_INPUT_BUFFER + 1];

const uint8_t g_cmd_header[] = "CMD> ";
const uint8_t g_cmd_line_break[3] = {0x0D, 0x0A, 0};

/*******************************************************************************
 * Function name  : CMD_ResetInput
 * Interface      : void CMD_ResetInput(void)
 * Description    : Reset CMD input index
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_ResetInput(void)
{
    g_cmd_current_index = 0;
    g_cmd_is_received = 0;
    g_cmd_is_cmd_entered = 0;
}

/*******************************************************************************
 * Function name  : CMD_Start
 * Interface      : void CMD_Start(void)
 * Description    : Start CMD application
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_Start(void)
{
    CMD_ResetInput();
    
    /* Device driver start */
    CMD_DRIVER_START();
    
    /* Start receiving data */
    CMD_DRIVER_RECEIVE(&g_cmd_received_byte, 1);
}

/*******************************************************************************
 * Function name  : CMD_SendByte
 * Interface      : void CMD_Start(uint8_t byte)
 * Description    : Send a byte to serial
 * Arguments      : uint8_t byte: byte to send
 * Return value   : None
*******************************************************************************/
void CMD_SendByte(uint8_t byte)
{
    CMD_DRIVER_SEND(&byte, 1);
}

/*******************************************************************************
 * Function name  : CMD_SendString
 * Interface      : void CMD_SendString(uint8_t *ptr_buffer)
 * Description    : Send a string (\0 ended) to serial 
 * Arguments      : uint8_t *ptr_buffer: pointer to string
 * Return value   : None
*******************************************************************************/
void CMD_SendString(uint8_t *ptr_buffer)
{
    uint16_t len = strlen(ptr_buffer);

    CMD_DRIVER_SEND(ptr_buffer, len);
}

/*******************************************************************************
 * Function name  : CMD_SendHeader
 * Interface      : void CMD_SendHeader(void)
 * Description    : Send command header
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_SendHeader(void)
{
    CMD_SendString((uint8_t *)g_cmd_header);
}

/*******************************************************************************
 * Function name  : CMD_SendLineBreak
 * Interface      : void CMD_SendLineBreak(void)
 * Description    : Send line break
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_SendLineBreak(void)
{
    CMD_SendString((uint8_t *)g_cmd_line_break);
}

/*******************************************************************************
 * Function name  : CMD_Printf
 * Interface      : void CMD_Printf(const uint8_t *format, ...)
 * Description    : Printf with format: consider code size
 *                : Code size could be reduce if no floating point number support
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_Printf(const uint8_t *format, ...)
{
    uint8_t buffer[CMD_PRINTF_BUFFER];
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    buffer[CMD_PRINTF_BUFFER - 1] = 0;

    CMD_SendString(buffer);
}

const uint8_t g_command_info_format[] = "%-10s%-25s\n\r";

void CMD_PrintCommandInstruction(void)
{
    CMD_SendLineBreak();
    CMD_Printf("Command Information\n\r");
    CMD_SendString("-----------------------------------\n\r");
    CMD_Printf(g_command_info_format, "Input", "Function");
    CMD_Printf(g_command_info_format, "?", "Help");
    CMD_Printf(g_command_info_format, "r", "Reset the MCU");
    CMD_Printf(g_command_info_format, "0", "Toggle disabled");
    CMD_Printf(g_command_info_format, "1", "Toggle interval: 0.5s");
    CMD_Printf(g_command_info_format, "2", "Toggle interval: 2.0s");
    CMD_Printf(g_command_info_format, "3", "Toggle interval: 3.0s");
    CMD_Printf(g_command_info_format, "4", "Toggle interval: 4.0s");
    CMD_Printf(g_command_info_format, "5", "Toggle interval: 5.0s");
    CMD_Printf(g_command_info_format, "6", "Toggle interval: 6.0s");
    CMD_Printf(g_command_info_format, "7", "Toggle interval: 7.0s");
    CMD_Printf(g_command_info_format, "8", "Toggle interval: 8.0s");
    CMD_Printf(g_command_info_format, "9", "Toggle interval: 9.0s");
}

uint8_t CMD_InputProcessing(void)
{
    uint8_t is_enter_key;

    if (g_cmd_received_byte == CMD_KEY_ENTER)
    {
        is_enter_key = 1;
    }
    else
    {
        is_enter_key = 0;

        if (g_cmd_current_index < CMD_MAX_INPUT_BUFFER)
        {
            g_cmd_input_buffer[g_cmd_current_index] = g_cmd_received_byte;
            g_cmd_current_index++;
            g_cmd_is_received = 1;
        }
    }

    return is_enter_key;
}

void CMD_AnalyzeResponse(void)
{
}

/*******************************************************************************
 * Function name  : CMD_ReceiveCallBack
 * Interface      : void CMD_ReceiveCallBack(void)
 * Description    : Interrupt receive callback for CMD application
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_ReceiveCallBack(void)
{
    /* Call to input processing */
    g_cmd_is_cmd_entered = CMD_InputProcessing();

    /* Start new receive */
    CMD_DRIVER_RECEIVE(&g_cmd_received_byte, 1);
}


/*******************************************************************************
 * Function name  : CMD_PollingProcessing
 * Interface      : void CMD_PollingProcessing(void)
 * Description    : Polling processing for CMD application
 * Arguments      : None
 * Return value   : None
*******************************************************************************/
void CMD_PollingProcessing(void)
{
    if (g_cmd_is_received == 1)
    {
        /* Send back received char to display on terminal */
        CMD_SendByte(g_cmd_input_buffer[g_cmd_current_index - 1]);

        g_cmd_is_received = 0;
    }

    if (g_cmd_is_cmd_entered == 1)
    {
        /* Is there any command in input buffer? */
        if (g_cmd_current_index <= CMD_MAX_INPUT_BUFFER)
        {
            /* Do based on user input */
            if (g_cmd_current_index != 0)
            {
                if (g_cmd_input_buffer[0] == '?')
                {
                    /* Print out possible input command */
                    CMD_PrintCommandInstruction();
                }
                else if (g_cmd_input_buffer[0] == 'r')
                {
                    NVIC_SystemReset();
                }
                else if (g_cmd_input_buffer[0] >= '0' &&
                         g_cmd_input_buffer[0] <= '9')
                {
            
                }
                else
                {
                    CMD_SendLineBreak();
                    CMD_SendString("Unknown command, type '?' for help");
                    CMD_SendLineBreak();
                }
            }
        }

        /* Reset receive buffer */
        CMD_ResetInput();
        CMD_SendLineBreak();
        CMD_SendHeader();

        g_cmd_is_cmd_entered = 0;
    }
}