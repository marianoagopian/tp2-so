// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "./include/syscalls.h"
#include "./include/test_util.h"
#include "./include/commands.h"
#include "./include/functions.h"

#define SEM_ID 2345
#define TOTAL_PAIR_PROCESSES 2
#define MAX 500

static unsigned int global; // shared memory

void slowInc(unsigned int *p, int inc) {
  int aux;
  aux = *p;
  aux += inc;
  for(int i = 0; i < 30000 ; i++) 
    ;
  *p = aux;
}

void my_process_inc(char *argv[]) {
  int inc = 1;

  int i;
  for (i = 0; i < MAX; i++) {
    if (argv[1][0] == 's') {
      sys_wait_sem(SEM_ID);
    }
    slowInc(&global, inc);
    if (argv[1][0] == 's') {
      sys_signal_sem(SEM_ID);
    }
  }
}

uint64_t test_sync(char** argv) {
  int semUse = satoi(argv[1]);
  if(semUse) {
    sys_destroy_sem(SEM_ID);
    int res = sys_register_sem(SEM_ID, 1);
    if (res != 0) {
      printf("test_sync: ERROR opening semaphore\n");
      return -1;
    }
  }

  char *args[] = {"sem", NULL, NULL};

  global = 0;

  if(semUse) {
    args[1] = "s";
  }

  int i;
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    int error = sys_register_child_process((uint64_t)&my_process_inc, STDIN, BACKGROUND, (uint64_t) args);
    if (error <= 0 ) {
      printf("Error creating children");
    }
  }

  sys_wait_for_children();

  if(semUse) {
    sys_destroy_sem(SEM_ID);
  }

  printf("Global expected value: %d. Global final value: %d\n", MAX * TOTAL_PAIR_PROCESSES, global);

  return 0;
}
