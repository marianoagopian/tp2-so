#include <stdint.h>
#include <stdio.h>
#include "./include/syscalls.h"
#include "./include/test_util.h"
#include "./include/commands.h"


#define SEM_ID 2345
#define TOTAL_PAIR_PROCESSES 2

int64_t global; // shared memory

void slowInc(int64_t *p, int64_t inc) {
  uint64_t aux = *p;
  aux += inc;
  for(int i = 0; i < 300000 ; i++) ;
  *p = aux;
}

uint64_t my_process_inc(uint64_t argc, char *argv[]) {
  uint64_t n;
  int8_t inc;
  int8_t use_sem;

  if (argc != 3)
    return -1;

  if ((n = satoi(argv[0])) <= 0)
    return -1;
  if ((inc = satoi(argv[1])) == 0)
    return -1;
  if ((use_sem = satoi(argv[2])) < 0)
    return -1;

  if (use_sem)
    if (!sys_register_sem(SEM_ID, 1)) {
      printf("test_sync: ERROR opening semaphore\n");
      return -1;
    }

  uint64_t i;
  for (i = 0; i < n; i++) {
    if (use_sem)
      sys_wait_sem(SEM_ID);
    slowInc(&global, inc);
    if (use_sem)
      sys_signal_sem(SEM_ID);
  }

  if (use_sem)
    sys_destroy_sem(SEM_ID);

  return 0;
}

uint64_t test_sync() { //{n, use_sem, 0}

  char *argvDec[] = {"3", "-1", "1", NULL};
  char *argvInc[] = {"2", "1", "0", NULL};

  global = 0;

  uint64_t i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    sys_register_process((uint64_t)&my_process_inc, 1, 1, (uint64_t) argvDec);
    sys_register_process((uint64_t) &my_process_inc, 1, 1, (uint64_t) argvInc);
  }

  sys_wait_for_children();

  printf("Final value: %d\n", global);

  return 0;
}
