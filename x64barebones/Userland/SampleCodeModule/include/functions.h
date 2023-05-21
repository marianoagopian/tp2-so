#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

void putchar(char c);

void print(const char* buf, uint64_t count);

char getChar();

void scanf(char* readbuf, uint64_t maxlen);

void clearScreen();

int strlen(const char * str);

int strcmp(const char * str1, const char* str2);

void infoReg();

void printf(char *fmt,...);

void reverseString(char * string, int length);

int intToString(int num, char *buffer);

void screenSize(int *width, int *height);

#endif