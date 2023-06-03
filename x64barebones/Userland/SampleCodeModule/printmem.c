#include "./include/functions.h"
#include "./include/syscalls.h"

#define BUFFER_LENGTH 150
#define INVALID_POS -1

static char * invalidArgument = "Invalid argument!\nArgument must be number!\n";
static char * invalidMemoryAddress = "Invalid memory address!\n";
static char * noArgument = "For this function argument is necessary\n";

void printmem(char * arg) {
    if(*arg == 0) {
        print(noArgument, strlen(noArgument)); //si no pasaron parametro enviamos el mensaje
        return;
    }
    if(!isNum(arg)) {                                            // recibe un string que puede o no ser un numero
        print(invalidArgument, strlen(invalidArgument));
        return;
    }
    uint64_t position = aToI(arg);


    char buffer[BUFFER_LENGTH] = {0};

    if(sys_printmem(position, buffer) == INVALID_POS){
        print(invalidMemoryAddress, strlen(invalidMemoryAddress));
    }
    else {
        print(buffer, strlen(buffer));
        print("\n",1);
    }
}
