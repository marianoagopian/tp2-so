#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <video.h>
#include <time.h>

#define REGISTERS 15

int sysWrite(int fd, char * buf, int count);

void sysClear();

unsigned int sysRead(unsigned int fd, char * buf, unsigned int count);

void saveInfoReg(uint64_t * regDumpPos);

int sysInfoReg(uint64_t * buffer);

char sysCheckBuffer();

void sysClearBuffer(); 

unsigned int sysPrintmem(uint64_t position, char * buffer);

int sysTime();

int sysGetLevel();

void sysSetLevel(int level);

void sysHolder(int time);

void sysDrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);

void sysBeep(uint32_t frequence);

void sysStop();

#endif