#include <commands.h>
#include <functions.h>
#include <exceptions.h>
#include <syscalls.h>

#define PARAMETERS_ERROR "Parameters are not needed for this command, try without them.\n"

static const char* commands[COMMANDS_QTY] = { "clear", "changeFontSize", "divbyzero", "help", "inforeg",  "invalidopcode", "printmem",  "time", "tron" };

void checkCommand(char command[BUFFER_LENGTH], char parameter[PARAMETER_LENGTH], char readbuf[BUFFER_LENGTH]) {
	int i, j;
	
	for(i=0, j=0; i<BUFFER_LENGTH && readbuf[i] != ' '; i++){
			command[j++] = readbuf[i]; // pasamos el buffer al nombre del comando
	}

	command[j] = 0;

	while(i < BUFFER_LENGTH && readbuf[i] == ' '){ // Elimino el/los espacios entre el comando llamado y el parametro
		i++;
	}

	for(j = 0; i < BUFFER_LENGTH && readbuf[i] != ' ' ; ) {
		if(j >= PARAMETER_LENGTH) {
			return;
		}
		parameter[j++] = readbuf[i++]; // pasamos el parametro a parameter
	}
	parameter[j] = 0;
}

static void invalidCommand() {
	print(INVALID_COMMAND_MSG, strlen(INVALID_COMMAND_MSG));
}

void callFunction(char * command, char * parameter) {
	int functionIndex = -1;
	int i;
	for(i = 0; i < COMMANDS_QTY && functionIndex == -1; i++) {
		if(strcmp(command, commands[i]) == 0) {
			functionIndex = i;
		}
	}
	if((functionIndex != 6 && functionIndex != 1 && functionIndex != -1) && *parameter != 0) {
    	print(PARAMETERS_ERROR, strlen(PARAMETERS_ERROR));
    return;
  	}
	switch (functionIndex) {  // buscamos el comando en el vector de comandos
    case 0:
    sys_clear_screen();
      break;
    case 1:
      changeFontSize(parameter);
      break;
    case 2:
      divByZero();
      break;
    case 3:
      help();
      break;
    case 4:
      infoReg();
      break;
    case 5:
      invalidOperationCode();
      break;
    case 6:
      printmem(parameter);
      break;
    case 7:
      time();
      break;
    case 8:
      tron();
      break;
    default:
      invalidCommand();
      break;
    }
}
