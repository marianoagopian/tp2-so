#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

uint64_t aToI(const char * string);

uint8_t isNum(const char * string);

void putchar(char c);

void print(const char* buf, uint64_t count);

char getChar();

void scanf(char* readbuf, uint64_t maxlen);

void clearScreen();

int strlen(const char * str);

int strcmp(const char * str1, const char* str2);

int strncpy(char * dest, const char * src, unsigned int n);

void infoReg();

void printf(char *fmt,...);

void reverseString(char * string, int length);

int intToString(int num, char *buffer);

void screenSize(int *width, int *height);

void * memset(void * destiation, int32_t c, uint64_t length);

#endif