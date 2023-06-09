#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <stdint.h>

#define COMMANDS_QTY 9
#define PARAMETER_LENGTH 10
#define BUFFER_LENGTH 256

#define INVALID_COMMAND_MSG "-Invalid command. Check available commands with help.\n"
#define INVALID_PID_MSG "Invalid PID: No such process is running.\n"
#define ERROR_PID -1

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]);

void callFunction(char * command, char * parameter);

void sys_clear_screen();

void changeFontSize(char ** par);

void ps();

void loop();

void kill(char ** args);

void nice(char ** args);

void block(char ** args);

void cat();

void wc();

void filter();

void mem_status();

void divByZero();

void help();

void infoReg();

void invalidOperationCode();

void printmem(char *arg);

void time();

void tron();

void phylo();

//tests

void test_mm();

void test_prio();

int64_t test_processes(char *argv[]);

uint64_t test_sync(char **argv);

#endif
