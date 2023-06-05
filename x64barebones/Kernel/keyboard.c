#include <keyboard.h>
#include <stdint.h>
#include <video.h>
#include <interrupts.h>
#include <lib.h>
#include <syscalls.h>
#include <multitasking.h>

static const char scanCodeTable[256] = {
    0,  ESCAPE,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=', '\b',
    '\t', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '[',   ']',  '\n',
    0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l', ';' ,  '|',
    0,    0,  0,   'z',  'x',  'c', 'v', 'b',  'n',  'm',  ',',  '.',  '/',    0,
    '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

/*-------- CONSTANTS --------*/
#define BUFFER_SIZE 200

/*-------- STATIC FILE VARIABLES --------*/
static char keyBuffer[BUFFER_SIZE];             // Buffer for keyboard characters 
static int writePos;				// Position in buffer for writing
static int index = 0;
static int ctrl = 0;


void keyboard_handler(uint64_t * regDumpPos) {
	int c = getKey();

	if (scanCodeTable[c] == ESCAPE) {
		saveInfoReg(regDumpPos);
		return;
	}

  if (c == CTRL) {
    ctrl = 1;
    return;
  } else if(ctrl && scanCodeTable[c] == 'c') {
    cleanKeyboardBuffer();
    kill_screen_processes();
    printNewline();
    ctrl = 0;
    return;
  } else if(ctrl && scanCodeTable[c] == 'd') {
    keyBuffer[writePos++] = EOF;
    ctrl = 0;
    return;
  } else {
    ctrl = 0;
  }
    
	if(writePos < BUFFER_SIZE) {
		keyBuffer[writePos++] = c;
  }
}


unsigned int readKeyboardCharacters(char * buf, unsigned int n) {
  _cli();
  unsigned int charsRead = 0;
  unsigned int scancodeIndex;
  for (scancodeIndex = 0; scancodeIndex < writePos && charsRead < n; scancodeIndex++) {
    if (keyBuffer[scancodeIndex] == -1) {
      buf[charsRead++] = keyBuffer[scancodeIndex];
      printNewline();
    }

    unsigned char c = keyBuffer[scancodeIndex];

    if (c > 0 && c < 128){
      buf[charsRead++] = scanCodeTable[c];
    } 
  }
  writePos -= scancodeIndex;
  memcpy(keyBuffer, keyBuffer + scancodeIndex, writePos);
  _sti();
  return charsRead;
}

void cleanKeyboardBuffer() {
  for(int i = 0 ; i < writePos ; i++){
    keyBuffer[i] = 0;
  } 
  writePos = 0;
  index = 0;
}

char checkKeyboardBuffer() {
  if(index < writePos) {
    return keyBuffer[index++];
  }
  return keyBuffer[index];
}
