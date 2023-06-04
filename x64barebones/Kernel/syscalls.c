#include <keyboard.h>
#include <video.h>
#include <stdint.h>
#include <defs.h>
#include <lib.h>
#include <interrupts.h>
#include <RTC.h>
#include <time.h>
#include <speaker.h>
#include "../include/multitasking.h"
#include "../include/memoryManager.h"
#include "../include/pipes.h"
#include "../include/semaphore.h"

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


void sysClear() {
  clean_screen();
}

unsigned int sysRead(unsigned int fd, char * buf, unsigned int count){
	unsigned int totalRead = 0;
    do {
        _hlt();
        totalRead = readKeyboardCharacters(buf + totalRead, count - totalRead);
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

uint64_t sysAlloc(uint64_t len) {
	return (uint64_t) mm_malloc(len);
}

uint64_t sysNice(uint8_t pid, int delta){
	return change_priority(pid, delta);
}

uint64_t sysDestroyPipe(unsigned int pipe_id){
	destroy_pipe(pipe_id);
	return 1;
}

uint64_t sysDestroySem(unsigned int sem_id){
	destroy_sem(sem_id);
	return 1;
}

uint64_t sysFree(void * ptr) {
	mm_free(ptr);
	return 1;	
}

uint64_t sysGetPid(){
	return get_current_pid();
}

uint64_t sysKillProcess(unsigned int pid) {
	return removeTask(pid);
}

uint64_t sysMmStatus(uint64_t * buffer){
	printMemStatus(buffer);
	return 1;
}

uint64_t sysPauseProcess(unsigned int pid) {
	return pauseOrUnpauseProcess(pid);
}

uint64_t sysPipeInfo(pipes_info * info){
	return get_pipe_info(info);
}

uint64_t sysProcessAlive(unsigned int pid){
	return findTask(pid) != NO_TASK_FOUND;
}

uint64_t sysProcessInfo(process_info * info){
	return get_process_info(info);
}

uint64_t sysReadPipe(unsigned int pipe_id, char * dest, unsigned int count){
	return read_from_pipe(pipe_id, dest, count);
}

uint64_t sysRegisterChildProcess(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0){
	return add_child_task(entryPoint, input, output, arg0);
}

uint64_t sysRegisterPipeAvailable(){
	return create_pipe_available();
}

uint64_t sysRegisterPipe(unsigned int pipe_id){
	return create_pipe(pipe_id);
}

uint64_t sysRegisterProcess(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0){
	return add_task(entrypoint, input, output, DEFAULT_PRIORITY, MORTAL, arg0);
}

uint64_t sysRegisterSem(unsigned int sem_id, unsigned int value){
	return create_sem(sem_id, value);
}

uint64_t sysRegisterSemAvailable(unsigned int value){
	return create_sem_available(value);
}

uint64_t sysRenounceCpu(){
	forceChangeTask();
	return 1;
}

uint64_t sysSemaphoreInfo(semaphore_info * info){
	return get_semaphore_info(info);
}

uint64_t sysSignalSem(unsigned int sem_id){
	return signal_sem(sem_id);
}

uint64_t sysWaitForChildren(){
	wait_for_children();
	return 1;
}

uint64_t sysWaitSem(unsigned int sem_id){
	return wait_sem(sem_id);
}

uint64_t sysWrite(unsigned int fd, const char * buf,unsigned int count) {
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
/*
uint64_t sysWrite(unsigned int fd, const char *buf, unsigned int count){
	return writeDispatcher(fd, buf, count);
}*/

uint64_t sysWritePipe(unsigned int pipe_id, const char * src, unsigned int count){
	return write_to_pipe(pipe_id, src, count);
}

uint64_t sysWriteToScreen(const char *buf, unsigned int count) {
	return sysWrite(get_current_output(),buf,count);			
}