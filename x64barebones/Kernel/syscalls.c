#include <keyboard.h>
#include <video.h>
#include <stdint.h>
#include <defs.h>
#include <lib.h>
#include <interrupts.h>
#include <RTC.h>
#include <time.h>
#include <speaker.h>

#define MAX_MEM_READ 16
#define BYTE_LENGTH 2
#define MAX_MEM_POS 0x7FFFFFFFF		/* 7 FFFF FFFFh tira page fault (34359738367 en dec )*/
#define MIN_MEM_POS 0x400000		/* Aca arranca Userland  (4194304 en dec)*/
#define INVALID_POS -1

static uint64_t infoReg[REGISTERS] = {0};

static int getFormat(int n) {
	int dec = n & 240;
	dec = dec >> 4;
	int units = n & 15;
	return dec * 10 + units;
}

int sysWrite(int fd, char * buf, int count) {
  if(fd != STDERR && fd != STDOUT) {
    return 0;
  }
  if (fd == STDERR) {
    setScreenPrintColor((Color){0x00, 0x00, 0xFF});
  }
	for (int i = 0; i < count; i++)
		printChar(buf[i]);
	setScreenPrintColor((Color){0x7F, 0x7F, 0x7F});
	
	return count;
}

void sysClear() {
  clean_screen();
}

unsigned int sysRead(unsigned int fd, char * buf, unsigned int count){
	unsigned int totalRead = 0;
	do {
			_hlt();
			totalRead += readKeyboardCharacters(buf + totalRead, count - totalRead);
		} while (totalRead == 0);

	return totalRead;
}

static int hasScreenshoted = 0;

void saveInfoReg(uint64_t * regDumpPos) {
	hasScreenshoted=1;
	for(int i = 0 ; i < REGISTERS ; i++) {
		infoReg[i] = regDumpPos[i];
	}
}

int sysInfoReg(uint64_t * buffer) {
	if(hasScreenshoted == 0){
		char *aux = "Press the ESCAPE button before calling inforeg";
		memcpy(buffer, aux, _strlen(aux));
		return 0;
	}
	for(int i = 0 ; i < REGISTERS ; i++) {
		buffer[i] = infoReg[i];
	}
	return 1;
}

int sysTime() {
  int hours = getFormat(_NRTCGetHours());
  int mins = getFormat(_NRTCGetMins());
  int seconds = getFormat(_NRTCGetSeconds());

  return hours * 3600 + mins * 60 + seconds;
}


unsigned int sysPrintmem(uint64_t position, char * buffer) {
	if( !(position >= MIN_MEM_POS && position < MAX_MEM_POS) )		// restringimos tmb que no pueda leer memoria de kernel
		return INVALID_POS;

	uint64_t current;
	
	for(int i=0, k=0; i < MAX_MEM_READ; i++) {
		if(i!=0 && i%4==0) {
			buffer[k++] = ' ';
    }
    current = *((uint8_t * )position + i);
    k += hexToString(current, buffer + k, BYTE_LENGTH);
	}

	return 0;
}

void sysClearBuffer() {
  cleanKeyboardBuffer();
}

char sysCheckBuffer() {
  return checkKeyboardBuffer();
}


int sysGetLevel() {
  return getLevel();
}

void sysSetLevel(int level) {
  setLevel(level);
}

void sysHolder(int time) {
  holder(time);
}

void sysBeep(uint32_t frequence) {
  beep(frequence);
}

void sysStop() {
  noSound();
}

void sysDrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color) {
  drawRect(x, y, width, height, color);
}
