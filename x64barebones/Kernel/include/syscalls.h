#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <video.h>
#include <time.h>
#include "./data_types.h"

#define REGISTERS 15

uint64_t sysWrite(unsigned int fd, const char * buf, unsigned int count);

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

/* New syscalls SO*/

uint64_t sysAlloc(uint64_t len);

uint64_t sysDestroyPipe(unsigned int pipe_id);

uint64_t sysDestroySem(unsigned int sem_id);

uint64_t sysFree(void * ptr);

uint64_t sysGetPid();

uint64_t sysKillProcess(unsigned int pid);

uint64_t sysMmStatus(uint64_t * buffer);

uint64_t sysPauseProcess(unsigned int pid);

uint64_t sysPipeInfo(pipes_info * info);

uint64_t sysProcessAlive(unsigned int pid);

uint64_t sysProcessInfo(process_info * info);

uint64_t sysReadPipe(unsigned int pipe_id, char * dest, unsigned int count);

uint64_t sysRegisterChildProcess(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);

uint64_t sysNais(uint8_t pid, int delta);

uint64_t sysRegisterPipeAvailable();

uint64_t sysRegisterProcess(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);

uint64_t sysRegisterSem(unsigned int sem_id, unsigned int value);

uint64_t sysRegisterSemAvailable(unsigned int value);

uint64_t sysRenounceCpu();

uint64_t sysSignalSem(unsigned int sem_id);

uint64_t sysWaitForChildren();

uint64_t sysWaitSem(unsigned int sem_id);

uint64_t sysWritePipe(unsigned int pipe_id, const char * src, unsigned int count);

uint64_t sysWriteToScreen(const char *buf, unsigned int count);
#endif