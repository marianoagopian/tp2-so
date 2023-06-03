#include "./include/syscalls.h"
#include <color.h>
#include "./include/functions.h"
#include <stdarg.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define REGISTERS 15
#define REGISTER_LENGTH 16
#define BUFF_SIZE 20

static const uint8_t scanCodeTable[256] = {
  0,    0,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '-',  '=',    '\b',
  '\t', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '[',   ']',  '\n',
  0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\'',
  0,    0,  '\\',   'z',  'x',     'c', 'v', 'b',  'n',  'm',  ',',  '.',  '/',    0,
  '*',     0,  ' ',    0,     0,     0,    0,       0,         0,
};

void putchar(char c) {
    print(&c, 1);
}

void print(const char* buf, uint64_t count) {
    sys_write(STDOUT, buf, count);
}

void clearScreen() {
    sys_clear_screen();
}

char getChar() {
	char c;

  while (sys_read(STDIN, &c, 1) == 0){
      ;
  }
	return c;
}

void scanf(char* readbuf, uint64_t maxlen) {
    if (maxlen == 0)
        return;

    // Leemos hasta maxlen-1 caracteres
    uint64_t count = 0;
    do {
        char c = getChar();

        if (c == '\n') { // Si llegamos hasta \n termino el string
            readbuf[MIN(count, maxlen-1)] = '\0';
            print(&c, 1);
            return;
        } 
        if (c == '\b'){ 
            if (count != 0){
                count--;
            }
            print(&c, 1);
        }
         else {
            //Agregamos el caracter al buffer 
	        print(&c, 1);
            if (count < maxlen-1 && c != 0) {
                readbuf[count] = c;
                count++;
            }
        }
    } while (1);
}

int strlen(const char * str) {
	int ans = 0;
	for (int i = 0; str[i] != 0; i++) {
		ans++;
	}
    return ans;
}

int strncpy(char * dest, const char * src, unsigned int n){
    int i=0;
    for(; src[i]!=0 && i<n; i++){
        dest[i] = src[i];
    }
    dest[i] = 0;
    return i;
}

int strcmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void reverseString(char * string, int length) {
    char aux;
    for(int i = 0, j = length - 1; i < j ; i++, j--) {
        aux = string[i];
        string[i] = string[j];
        string[j] = aux;
    }
}

int intToString(int num, char *buffer) {
    if(num==0) {
        buffer[0] = '0';
        buffer[1] = 0;
        return 2;
    }
    int i = 0;
    while(num > 0) {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    }
    reverseString(buffer, i);
    buffer[i] = 0;
    return i;
}

void printf(char *fmt,...){     //funcion de print con funcionalidad similar a la brindada por stdio.h
    va_list ap; 
    char *p, *sval;
    int ival;

    va_start(ap, fmt);
    char *aux = {0};
    int len = 0;
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                len = intToString(ival, aux);
                print(aux,len);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); 
}

void * memset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}

uint64_t aToI(const char * string) {
    uint64_t result = 0;

    for(int i = 0 ; string[i] ; i++) {
        result = result*10 + string[i] - '0';
    }

    return result;
}

uint8_t isNum(const char * string) {
    for(int i=0; string[i]!=0; i++) {
        if(string[i]>'9' || string[i]<'0') {
            return 0;
        }
    }
    return 1;
}
