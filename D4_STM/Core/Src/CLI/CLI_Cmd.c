/*
 * CLI_Cmd.c
 *
 *  Created on: Jan 30, 2025
 *      Author: felix
 */

#include "CLI.h"
#include <stdlib.h>
#include "CLI_Cmd.h"
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#define NUMER_OF_CMD		(1)


static char bufferTX[150] = {0};
//static char bufferStats[512] = {0};

/* DONT FORGET TO UPDATE THE DEFINE WHEN ADDING A COMMAND*/ //TODO FIX this


CLI_Command_Definition_t CLI_def[] =
{{	.pcCommand = "Hello",
	.pcHelpString = "Hello\n\r",
	.pxCommandInterpreter = CLICmd_Hello_Func,
	.cExpectedNumberOfParameters = 0}

};


void CLICmd_RegisterCMD(void)
{
	CLI_Register_CMD(CLI_def, NUMER_OF_CMD);
}

/*
 *
 *
 *
 *
 *
 *
 *
*/

BaseType_t CLICmd_Hello_Func(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{

	uint16_t uSize = snprintf(bufferTX, sizeof(bufferTX), "HelloUART\n\r");
	CLI_Send((uint8_t*)bufferTX, uSize);

	return 0;
}


