#include <commands.h>
#include <functions.h>
#include <syscalls.h>


void time(){
    int aux = sys_time();
    if(aux < 3600 * 3) {   // hay que restarle 3 ya que Buenos Aires es UTC-3 y sys_time devuelve en UTC
        aux += 3600 * 21;
    } else {
        aux -= 3600 * 3;
    }
    int hours = aux / 3600;
    int minutes = (aux - hours * 3600) / 60;
    int seconds = aux % 60;

    printf("%d:%d:%d\n", hours, minutes, seconds);
}