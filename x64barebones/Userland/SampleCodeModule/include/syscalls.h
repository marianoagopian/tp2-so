#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>
#include <color.h>
#include "data_types.h"

#define STDIN 1
#define STDOUT 1
#define STDERR 2

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


/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16

uint64_t sys_read(uint64_t fd, const char* buf, unsigned int length);
uint64_t sys_write(uint64_t fd, const char* buf, uint64_t count);
uint8_t sys_info_reg(uint64_t reg[15]);
uint64_t sys_time();
void sys_clear_screen();
void sys_beep(uint32_t frequency);
uint64_t sys_printmem(uint64_t position, char * buffer);
void sys_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);
uint8_t sys_check_buffer();
void sys_holder(int time);
void sys_clear_buffer();
void sys_set_level(int num);
uint64_t sys_get_level();
void sys_stop();

uint64_t sys_alloc(uint64_t len);
uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_destroy_sem(unsigned int sem_id);
uint64_t sys_free(void * ptr);
uint64_t sys_get_pid();
uint64_t sys_kill_process(unsigned int pid);
uint64_t sys_mm_status(uint64_t * buffer);
uint64_t sys_nice(uint8_t pid, int delta);
uint64_t sys_pause_process(unsigned int pid);
uint64_t sys_process_alive(unsigned int pid);
uint64_t sys_pipe_info(pipes_info * info);
uint64_t sys_process_info(process_info * info);
uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count);
uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0);
uint64_t sys_register_pipe_available();
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0);
uint64_t sys_register_sem(unsigned int sem_id, unsigned int value);
uint64_t sys_register_sem_available(unsigned int value);
uint64_t sys_renounce_cpu();
uint64_t sys_signal_sem(unsigned int sem_id);
uint64_t sys_wait_for_children();
uint64_t sys_wait_sem(unsigned int sem_id);
uint64_t sys_write_pipe(unsigned int pipe_id, const char * src, unsigned int count);
#endif
