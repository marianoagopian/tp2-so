#include <stdint.h>
#include "./include/syscalls.h"
#include "./include/test_util.h"
#include "./include/commands.h"
#include "./include/functions.h"

#define MINOR_WAIT 1000000 
#define WAIT 50000000    

#define TOTAL_PROCESSES 3
#define LOWEST 1  
#define MEDIUM 3 
#define HIGHEST 5 

int64_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};

void test_prio() {
  int64_t pids[TOTAL_PROCESSES];
  char *argv[] = {0};
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = sys_register_process((uint64_t) &endless_loop_print, 1, 1, (uint64_t) argv);

  bussy_wait(WAIT);
  printf("\nCHANGING PRIORITIES...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], prio[i]);

  bussy_wait(WAIT);
  printf("\nBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_pause_process(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], MEDIUM);

  printf("UNBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_pause_process(pids[i]);

  bussy_wait(WAIT);
  printf("\nKILLING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_kill_process(pids[i]);
}
