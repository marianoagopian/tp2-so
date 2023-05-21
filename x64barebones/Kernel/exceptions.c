#include <stdint.h>
#include <syscalls.h>
#include <lib.h>
#include <defs.h>
#include <interrupts.h>
#include <keyboard.h>

extern void resetmain(void);

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPERATION_CODE_ID 6

static void zeroDivision(uint64_t * registerDumpPos);
static void invalidOpCode(uint64_t * registerDumpPos);
static void handlerException();

void exceptionDispatcher(int exception, uint64_t * registerDumpPos) {
  switch (exception) {
    case ZERO_EXCEPTION_ID:
      zeroDivision(registerDumpPos);
      break;
    
    case INVALID_OPERATION_CODE_ID:
      invalidOpCode(registerDumpPos);
      break;
    }
}

static void zeroDivision(uint64_t * registerDumpPos) {
	handlerException("An exception has occurred dividing by zero\n", registerDumpPos);
}

static void invalidOpCode(uint64_t * registerDumpPos) {
	handlerException("An exception has occurred because it was used an invalid operation code\n", registerDumpPos);
}

static void handlerException(char * msg, uint64_t * registerDumpPos) {
  sysWrite(STDERR, msg, _strlen(msg));
  printRegisters(registerDumpPos);
  sysWrite(STDERR, "Press any key to continue.", _strlen("Press any key to continue"));

  cleanKeyboardBuffer();
  char *aux = {0};
  do { _hlt(); sysRead(STDOUT, aux, 2); } while(*aux == 0);

  cleanKeyboardBuffer();
  clean_screen();
  _cli();
  resetmain();
}
