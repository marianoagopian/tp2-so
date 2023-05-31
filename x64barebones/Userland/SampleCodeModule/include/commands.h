#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define COMMANDS_QTY 9
#define PARAMETER_LENGTH 10
#define BUFFER_LENGTH 256

#define INVALID_COMMAND_MSG "-Invalid command. Check available commands with help.\n"

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]);

void callFunction(char * command, char * parameter);

void sys_clear_screen();

void changeFontSize(char *par);

void divByZero();

void help();

void infoReg();

void invalidOperationCode();

void printmem(char *arg);

void time();

void tron();

//tests

void test_mm();

void test_prio();

void test_processes();



#endif
