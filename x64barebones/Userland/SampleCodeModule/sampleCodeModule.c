/* sampleCodeModule.c */
#include <stdint.h>
#include <color.h>
#include <syscalls.h>
#include <functions.h>
#include <commands.h>
#include <shell.h>

int main() {
	clearScreen();	
	shell();
	/*
	while(1) {
		print(newLine, strlen(newLine));
		char readBuffer[BUFFER_LENGTH] = {0};
		scanf(readBuffer, BUFFER_LENGTH);

		char parameter[PARAMETER_LENGTH] = {0};
		char command[BUFFER_LENGTH] = {0};

		checkCommand(command, parameter, readBuffer);

		callFunction(command, parameter);
	}*/
  return 1;
}
