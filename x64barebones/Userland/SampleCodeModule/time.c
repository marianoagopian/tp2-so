// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <commands.h>
#include <functions.h>
#include <syscalls.h>


void time(){
    int aux = sys_time();
    if(aux < 3600 * 3) {   //- 3 because BsAs is UTC-3 and sys_time works with UTC
        aux += 3600 * 21;
    } else {
        aux -= 3600 * 3;
    }
    int hours = aux / 3600;
    int minutes = (aux - hours * 3600) / 60;
    int seconds = aux % 60;

    printf("%d:%d:%d\n", hours, minutes, seconds);
}