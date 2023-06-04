#include "./include/commands.h"
#include "./include/syscalls.h"
#include "./include/functions.h"
#include <stdlib.h>

#define ACTIVE_PROCESS 1
#define PAUSED_PROCESS 2

#define NUM_LOOP 200000000 //0.2 sec

void ps(){

	process_info * info = sys_alloc(20 * sizeof(process_info)); //need a cast

	if(info == NULL) {
		printf("No more space\n");
		return;
	}

	uint64_t amount =  sys_process_info(info);

	for(int i = 0; i < amount; i++){
    
		printf("Name: %s\t\t|  ",info[i].name);
        printf("PID: %d\t\t|  ",info[i].id);
        printf("State: ");
		// state
		switch(info[i].state){
			case ACTIVE_PROCESS: 
				printf("Active\t\t|  ");
				break;
			case PAUSED_PROCESS:
				printf("Paused\t\t|  ");
				break;
			default:
				printf("Blocked\t\t|  ");
				break;
		}
        printf("Priority: %d\t\t|  ",info[i].priority);
        printf("Stack: %d\t\t|  ",info[i].stack);
        printf("RSP: %d\n",info[i].rsp);
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
    printf("Invalid argument!\nArgument must be number.");
    return;
  }
  uint64_t pid = aToI(args[1]);
  if (sys_kill_process(pid) == ERROR_PID){
    printf(INVALID_PID_MSG);
  }
  return;
}