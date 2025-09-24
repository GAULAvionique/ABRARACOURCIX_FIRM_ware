/*
 * CLI.h
 *
 *  Created on: Jan 29, 2025
 *      Author: felix
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "CLI.h"
#include "CLI_Cmd.h"
#include "usart.h"
#include "App_LED/led.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "semphr.h"

#define MAX_INPUT_LENGTH    50
#define MAX_OUTPUT_LENGTH   100

#define FIFO_MAX_CHAR		(100)

uint8_t cRxedChar = 0x00;

uint8_t *SentChars = NULL;
uint8_t sizeSentChars = 0;


uint8_t cRxCh[] = "Hello World!\n\r";
uint8_t cTxCh[FIFO_MAX_CHAR] = {0};
uint8_t uMessage = 0;

/* DONT FORGET TO UPDATE THE DEFINE WHEN ADDING A COMMAND*/ //TODO FIX this
SemaphoreHandle_t xSemaphore;

void CLI_Register_CMD(CLI_Command_Definition_t *CLI_def, uint8_t uQty)
{
	for(uint8_t uIndex = 0; uIndex < uQty; uIndex++)
	{
		FreeRTOS_CLIRegisterCommand(&CLI_def[uIndex]);
	}
}


void vCLI_Task()
{
    int8_t cInputIndex = 0;
    BaseType_t xMoreDataToFollow;
    xSemaphore = xSemaphoreCreateBinary( );
    static int8_t pcOutputString[MAX_OUTPUT_LENGTH], pcInputString[MAX_INPUT_LENGTH];

    for (;;)
    {
        xSemaphoreTake(xSemaphore, osWaitForever);

        if (cRxedChar != 0x00)
        {

            if (cRxedChar == '\r' || cRxedChar == '\n')
            {
                printf("\r\n");
                fflush(stdout);

                do
                {
                    xMoreDataToFollow =
                        FreeRTOS_CLIProcessCommand((char*)pcInputString,
                                                   (char*)pcOutputString,
                                                   MAX_OUTPUT_LENGTH
                        );

                    for (int x = 0; x < (xMoreDataToFollow == pdTRUE ? MAX_OUTPUT_LENGTH : strlen((char*)pcOutputString)); x++)
                    {
                        printf("%c", *(pcOutputString + x));
                        fflush(stdout);
                    }

                } while (xMoreDataToFollow != pdFALSE);

                cInputIndex = 0;
                memset(pcInputString, 0x00, MAX_INPUT_LENGTH);
                memset(pcOutputString, 0x00, MAX_INPUT_LENGTH);
            }
            else
            {

                if (cRxedChar == '\b')
                {

                    if (cInputIndex > 0)
                    {
                        cInputIndex--;
                        char uNULL[] = "\0";
                        pcInputString[cInputIndex] = (int8_t)uNULL[0]; //TODO Fix This
                    }
                }
                else
                {

                    if (cInputIndex < MAX_INPUT_LENGTH)
                    {
                        pcInputString[cInputIndex] = cRxedChar;
                        cInputIndex++;
                        printf("%c", cRxedChar);
                    }
                }
            }
            cRxedChar = 0x00;
            fflush(stdout);
        }
        LED_GreenSetState(OFF);
    }
}


static void FIFO_Update(uint8_t *uChar, uint16_t size)
{
	uMessage == FIFO_MAX_CHAR?(uMessage = 0):(uMessage = uMessage);
	cTxCh[uMessage] = cRxedChar;
	uMessage++;
}

void CLI_Init(void)
{
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)cRxCh, sizeof(cRxCh));
	HAL_UART_Receive_DMA(&huart1, &cRxedChar, 1);
}


void CLI_Send(uint8_t *uChar, uint16_t size)
{
	SentChars = uChar;
	sizeSentChars = size;
	HAL_UART_Transmit_DMA(&huart1, uChar, size);


}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	FIFO_Update(&cRxedChar, 0x1);
	HAL_UART_Receive_DMA(huart, &cRxedChar, 1);
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	memset(SentChars, 0x00, sizeSentChars);
}


