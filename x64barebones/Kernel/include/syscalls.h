#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <video.h>
#include <time.h>
#include "./data_types.h"

#define REGISTERS 15

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_INFOREG 2
#define SYS_TIME 3 
#define SYS_CLEAR_SCREEN 4
#define SYS_BEEP 5
#define SYS_PRINT_MEM 6
//#define SYS_DRAW_RECT 7
#define SYS_CHECK_BUFFER 8
#define SYS_HOLDER 9  
#define SYS_CLEAR_BUFFER 10
#define SYS_SET_LEVEL 11
#define SYS_GET_LEVEL 12
#define SYS_STOP 13

#define SYS_ALLOC 14
#define SYS_DESTROY_PIPE 15
#define SYS_DESTROY_SEM 16
#define SYS_FREE 17
#define SYS_GET_PID 18
#define SYS_KILL_PROCESS 19
#define SYS_MM_STATUS 20
#define SYS_NICE 21
#define SYS_PAUSE_PROCESS 22
#define SYS_PIPE_INFO 23
#define SYS_PROCESS_ALIVE 24
#define SYS_PROCESS_INFO 25
#define SYS_READ_PIPE 26
#define SYS_REGISTER_CHILD_PROCESS 27
#define SYS_REGISTER_PIPE_AVAILABLE 28
#define SYS_REGISTER_PROCESS 29
#define SYS_REGISTER_SEM 30
#define SYS_REGISTER_SEM_AVAILABLE 31
#define SYS_RENOUNCE_CPU 32
#define SYS_SIGNAL_SEM 33
#define SYS_WAIT_FOR_CHILDREN 34
#define SYS_WAIT_SEM 35
#define SYS_WRITE_PIPE 36

/*
#define SYS_REGISTER_PIPE 
#define SYS_SEMAPHORE_INFO
*/

uint64_t sysWrite(unsigned int fd, const char * buf, unsigned int count);

void sysClear();

int sysRead(unsigned int fd, char * buf, unsigned int count);

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

uint64_t sysNice(uint8_t pid, int delta);

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