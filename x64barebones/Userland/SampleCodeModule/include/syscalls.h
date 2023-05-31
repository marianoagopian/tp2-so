#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>
#include <color.h>
#include "data_types.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2


/* The width of a character in pixels. */
#define CHAR_WIDTH 9
/* The height of a character in pixels. */
#define CHAR_HEIGHT 16

uint64_t sys_read(uint64_t fd, char* buf, uint64_t count);
uint64_t sys_write(uint64_t fd, const char* buf, uint64_t count);
int sys_time();
void sys_clear_screen();
uint8_t sys_info_reg(uint64_t reg[15]);
unsigned int sys_printmem(uint64_t position, char * buffer);
void sys_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Color color);
void sys_clear_buffer();
char sys_check_buffer();
void sys_set_level(int num);
void sys_holder(int time);
int sys_get_level();
void sys_beep(uint32_t frequency);
void sys_stop();


uint64_t sys_alloc(uint64_t len);
uint64_t sys_destroy_pipe(unsigned int pipe_id);
uint64_t sys_destroy_sem(unsigned int sem_id);
uint64_t sys_free(void * ptr);
uint64_t sys_get_pid();
uint64_t sys_kill_process(unsigned int pid);
uint64_t sys_mm_status(uint64_t * buffer);
uint64_t sys_pause_process(unsigned int pid);
uint64_t sys_pipe_info(pipes_info * info);
uint64_t sys_process_alive(unsigned int pid);
uint64_t sys_process_info(process_info * info);
uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count);
uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, char ** arg0);
uint64_t sys_nais(uint8_t pid, int delta);
uint64_t sys_register_pipe_available();
uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, char ** arg0);
uint64_t sys_register_sem(unsigned int sem_id, unsigned int value);
uint64_t sys_register_sem_available(unsigned int value);
uint64_t sys_renounce_cpu();
uint64_t sys_signal_sem(unsigned int sem_id);
uint64_t sys_wait_for_children();
uint64_t sys_wait_sem(unsigned int sem_id);
uint64_t sys_write_pipe(unsigned int pipe_id, const char * src, unsigned int count);
uint64_t sys_write_to_screen(const char *buf, unsigned int count);
#endif
