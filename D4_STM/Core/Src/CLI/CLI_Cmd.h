/*
 * CLI_Cmd.h
 *
 *  Created on: Jan 30, 2025
 *      Author: felix
 */

#ifndef SRC_CLI_CMD_H_
#define SRC_CLI_CMD_H_

void CLICmd_RegisterCMD(void);

BaseType_t CLICmd_Hello_Func(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

BaseType_t CLICmd_RTStats(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
#endif /* SRC_CLI_CMD_H_ */
