/*
 * CLI.h
 *
 *  Created on: Jan 29, 2025
 *      Author: felix
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "main.h"
#include "FreeRTOS_CLI.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "cmsis_os.h"

void CLI_Init();
void CLI_Register_CMD(CLI_Command_Definition_t *CLI_def, uint8_t uQty);
void CLI_Send(uint8_t *uChar, uint16_t size);
void vCLI_Task();

#endif /* INC_CLI_H_ */
