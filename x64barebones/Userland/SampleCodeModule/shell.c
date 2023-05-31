#include "./include/shell.h"
#include <commands.h>
#include <functions.h>
#include <exceptions.h>
#include <syscalls.h>

#define PARAMETERS_ERROR "Parameters are not needed for this command, try without them.\n"
#define PIPE_ERROR "The program does not work with pipes, try without them.\n"
#define MISSING_ARGS "The program needs arguments.\n"
#define INVALID_PROGRAM "The program does not exist. Use the command help for help\n"
#define MALLOC_ERROR "Error allocating space for args!"

#define NEW_LINE "$>:"
#define PIPE "|"
#define MAX_COMMAND_WORDS 10

typedef struct programInfo {
  char * name;
  uint64_t ptrToFunction;
  uint8_t args;
  uint8_t pipe;
} programInfo;

#define PROGRAMS_QTY 5

static programInfo programs[] = {
  {.name = "clear", .ptrToFunction = (uint64_t) &sys_clear_screen, .args = 0, .pipe = 0},
  {.name = "changeFontSize", .ptrToFunction = (uint64_t) &changeFontSize, .args = 1, .pipe = 0},
  {.name = "divByZero", .ptrToFunction = (uint64_t) &divByZero, .args = 0, .pipe = 0},
  {.name = "help", .ptrToFunction = (uint64_t) &help, .args = 0, .pipe = 0},
  {.name = "inforeg", .ptrToFunction = (uint64_t) &infoReg, .args = 0, .pipe = 0},
  {.name = "invalidopcode", .ptrToFunction = (uint64_t) &invalidOperationCode, .args = 0, .pipe = 0},
  {.name = "printmem", .ptrToFunction = (uint64_t) &printmem, .args = 1, .pipe = 0},
  {.name = "time", .ptrToFunction = (uint64_t) &time, .args = 0, .pipe = 0},
  {.name = "tron", .ptrToFunction = (uint64_t) &tron, .args = 0, .pipe = 0}
};


int parseCommand(char ** command, char readBuf[BUFFER_LENGTH]) {
	int i = 0, commandWords = 0;
  //hola josesito pepe 
	
	for(int postSpace = 1; commandWords < MAX_COMMAND_WORDS && readBuf[i] != '\n' && readBuf[i] != 0; i++) {
    if(readBuf[i] == ' ') {
      postSpace = 1;
      readBuf[i] = 0;
    } else if(postSpace) {
      command[commandWords++] = readBuf + i; 
      postSpace = 0;
    }
	}

  readBuf[i] = 0;
  return commandWords;
}

void shell() {
  print("Welcome to Shell! Type \"HELP\" for a list of commands.\n\n", 55);
  char * command[MAX_COMMAND_WORDS] = {0};

  while(1) {
    print(NEW_LINE, strlen(NEW_LINE));
    char readBuffer[BUFFER_LENGTH] = {0};
    scanf(readBuffer, BUFFER_LENGTH);

    parseCommand(command, readBuffer);

    // callFunction(command, parameter);
  }
}