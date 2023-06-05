#ifndef	_KEYBOARD_H
#define _KEYBOARD_H

/*--------  DEPENDENCIES --------*/
#include <stdint.h>
#include <syscalls.h>

/* --- CONSTANTS  --- */
#define ESCAPE 19
#define CTRL 29
#define EOF -1

extern char getKey();

/*
 * << keyboard_handler >>
 * ----------------------------------------------------------------------
 *  Handles keyboard functionality
 * ----------------------------------------------------------------------
 *  Receives noo parameters
 *  Returns:
 *      1 <=> wrote buffer
 *      0 <=> otherwise
 */
void keyboard_handler();

unsigned int readKeyboardCharacters(char* buf, unsigned int n);

void cleanKeyboardBuffer();

char checkKeyboardBuffer();

#endif