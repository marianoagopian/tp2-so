// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "../include/defs.h"
#include "../include/syscalls.h"
#include "../include/lib.h"


/* printRegisters */
#define TOTAL_REGISTERS 15
#define REGISTER_LENGTH 16


void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

int _strlen(const char * str){
	int ans = 0;
	for (int i = 0; str[i] != 0; i++) {
		ans++;
	}
	return ans;
}

void reverseString(char * string, int length) {
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}

int hexToString(uint64_t num, char * buffer, int fixedLength) {
    int i = 0;

    for(int aux ; num > 0 ; i++, num/=16){
        aux = num % 16;
        if(aux < 10)                     // turn to hex
            buffer[i] = aux + '0';
        else
            buffer[i] = aux - 10 + 'A';

    }
    while(i<fixedLength) {                   // add 0 == end it with the desired length
        buffer[i++] = '0';
    }
    reverseString(buffer,i);
    buffer[i] = 0;

    return i;
}

static char * registerOrder[] = {
	"RAX: ","RBX: ","RCX: ","RDX: ",
	"RBP: ","RSI: ","RDI: ","R8:  ", 
	"R9:  ","R10: ","R11: ","R12: ",
	"R13: ","R14: ","R15: " 
};

void printRegisters(uint64_t * registerDumpPos) {
	char buffer[100];
	for(int i=0, j = TOTAL_REGISTERS - 1; i<TOTAL_REGISTERS ; i++, j--) {

		sysWrite(STDERR, registerOrder[i], _strlen(registerOrder[i])-1);			// print register

		int amount = hexToString(registerDumpPos[j], buffer, REGISTER_LENGTH + 1);					
		sysWrite(STDERR, buffer,amount);										// print register value
		sysWrite(STDERR, "\n",1);
	}
}
