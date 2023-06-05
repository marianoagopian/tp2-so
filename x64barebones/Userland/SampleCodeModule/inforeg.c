// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <functions.h>
#include <syscalls.h>

#define REGISTERS 15
#define REGISTER_LENGTH 16
#define BUFF_SIZE 20

static char * registerOrder[] = {
    "RAX: ","RBX: ","RCX: ","RDX: ",
    "RBP: ","RSI: ","RDI: ","R8:  ", 
    "R9:  ","R10: ","R11: ","R12: ",
    "R13: ","R14: ","R15: "
};

int hexToString(uint64_t num, char * buffer, int fixedLength) {
    int i = 0;

    for(int aux ; num > 0 ; i++, num/=16){
        aux = num % 16;
        if(aux < 10)                     // turn to hex
            buffer[i] = aux + '0';
        else
            buffer[i] = aux - 10 + 'A';

    }
    while(i < fixedLength) {                   
        buffer[i++] = '0';
    }
    reverseString(buffer,i); //we read it the other way around 
    buffer[i] = 0;

    return i;
}

void infoReg() {
    char stringBuffer[BUFF_SIZE];
    uint64_t regBuffer[REGISTERS];

    if(sys_info_reg(regBuffer) == 0){ 
        printf("%s\n", regBuffer);
        return;
    }
    for(int i = 0 ; i < REGISTERS ; i++) {
        hexToString(regBuffer[i], stringBuffer, REGISTER_LENGTH);
        print(registerOrder[i], strlen(registerOrder[i]));
        print(stringBuffer, BUFF_SIZE);
        print("\n", 2);
    }
}
