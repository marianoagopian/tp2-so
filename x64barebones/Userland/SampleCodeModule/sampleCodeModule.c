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

  return 1;
}
