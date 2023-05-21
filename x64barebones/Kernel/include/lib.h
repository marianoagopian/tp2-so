#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

int _strlen(const char * str);

char *cpuVendor(char *result);

void reverseString(char * string, int length);

int hexToString(uint64_t num, char * buffer, int fixedLength);

void printRegisters(uint64_t * registerDumpPos);

#endif