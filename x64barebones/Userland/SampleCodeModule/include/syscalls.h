#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#include <stdint.h>
#include <color.h>

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

#endif
