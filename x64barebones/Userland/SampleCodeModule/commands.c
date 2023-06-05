#include "./include/commands.h"
#include "./include/syscalls.h"
#include "./include/functions.h"
#include <stdlib.h>

#define ACTIVE_PROCESS 1
#define PAUSED_PROCESS 2
#define NUM_LOOP 200000000 //0.2 sec
#define EOF -1
#define BACKGROUND 0
#define FOREGROUND 1

void ps(){

	process_info * info = (void *)sys_alloc(20 * sizeof(process_info)); //need a cast

	if(info == NULL) {
		printf("No more space\n");
		return;
	}

	uint64_t amount =  sys_process_info(info);

	for(int i = 0; i < amount; i++){
		printf("Name: %s\t| ",info[i].name);
    printf("PID: %d\t| ",info[i].id);
    printf("State: ");
		// state
		switch(info[i].state){
			case ACTIVE_PROCESS: 
				printf("Active\t| ");
				break;
			case PAUSED_PROCESS:
				printf("Paused\t| ");
				break;
			default:
				printf("Blocked\t| ");
				break;
		}
    printf("Priority: %d\t| ",info[i].priority);
    printf("Stack: %d\t| ",info[i].stack);
    printf("RSP: %d\t| ",info[i].rsp);
    printf("Screen: ");
    switch(info[i].screen) {
      case BACKGROUND:
        printf("Background\n");
        break;
      case STDOUT:
        printf("Stdout\n");
        break;
      default:
        printf("Pipe\n");
        break;
    }
	}

	sys_free((void*)info);
}

void loop(){
	int pid = sys_get_pid();
	char *buffer = " Hello, I am process ID:";
	while(1){
		for(int i = 0; i < NUM_LOOP ; i++)
			;
		printf("%s%d\t",buffer, pid);
	}	
}

void kill(char ** args){
	if(!isNum(args[1])) { 
    printf("Invalid argument! Argument must be number.\n");
    return;
  }
  uint64_t pid = aToI(args[1]);
  if (sys_kill_process(pid) == ERROR_PID){
    printf(INVALID_PID_MSG);
  }
  return;
}

void nice(char ** args){
  if(!isNum(args[1]) && !isNum(args[2])) { 
      printf("Invalid argument! Arguments must be numbers.\n");
      return;
  }
  unsigned int pid = aToI(args[1]);
  int delta = aToI(args[2]);
  sys_nice(pid, delta);
}

void block(char ** args){
  if(!isNum(args[1])) { 
    printf("Invalid argument! Argument must be number.\n");
    return;
  }
  //check because the only blocked process is shell so cant test
  uint64_t pid = aToI(args[1]);
  sys_pause_process((unsigned int)pid);
  return;
}

//check eof result == sys_read has unsigned int result
void cat(){
  int c;
  while ((c = getChar()) != EOF) { // Read input until there's no more input
      putchar(c); // Print the character
  }
}


void wc(){
  int c, counter = 1;
  while ((c = getChar()) != EOF)
  {
    if (c == '\n')
      counter++;
  }
  printf("La cantidad de lineas escritas fueron: %d", counter);
  return;

}