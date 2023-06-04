#include "./include/shell.h"
#include <commands.h>
#include <functions.h>
#include <exceptions.h>
#include <syscalls.h>

#define PARAMETERS_ERROR "Parameters are not needed for this command, try without them.\n"
#define PIPE_ERROR "The program does not work with pipes, try without them.\n"
#define MISSING_ARGS "The program needs arguments.\n"
#define INVALID_PROGRAM "The program does not exist. Use the command help for help\n"
#define MALLOC_ERROR "Error allocating space for args!"

#define NEW_LINE "$>:"
#define PIPE "|"
#define MAX_COMMAND_WORDS 10
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

typedef struct programInfo {
  char * name;
  uint64_t ptrToFunction;
  uint8_t args;
  uint8_t pipe;
} programInfo;

#define PROGRAMS_QTY 19

static programInfo programs[] = {
  {.name = "clear", .ptrToFunction = (uint64_t) &sys_clear_screen, .args = 0, .pipe = 0},
  {.name = "changefontsize", .ptrToFunction = (uint64_t) &changeFontSize, .args = 1, .pipe = 0},
  {.name = "divbyzero", .ptrToFunction = (uint64_t) &divByZero, .args = 0, .pipe = 0},
  {.name = "help", .ptrToFunction = (uint64_t) &help, .args = 0, .pipe = 0},
  {.name = "inforeg", .ptrToFunction = (uint64_t) &infoReg, .args = 0, .pipe = 0},
  {.name = "invalidopcode", .ptrToFunction = (uint64_t) &invalidOperationCode, .args = 0, .pipe = 0},
  {.name = "printmem", .ptrToFunction = (uint64_t) &printmem, .args = 1, .pipe = 0},
  {.name = "time", .ptrToFunction = (uint64_t) &time, .args = 0, .pipe = 0},
  {.name = "ps", .ptrToFunction = (uint64_t) &ps, .args = 0, .pipe = 1},
  {.name = "loop", .ptrToFunction = (uint64_t) &loop, .args = 0, .pipe = 1},
  {.name = "kill", .ptrToFunction = (uint64_t) &kill, .args = 1, .pipe= 0},
  {.name = "nice", .ptrToFunction = (uint64_t) &nice, .args = 2, .pipe = 0},
  {.name = "block", .ptrToFunction = (uint64_t) &block, .args = 1, .pipe = 0},
  {.name = "cat", .ptrToFunction = (uint64_t) &cat, .args = 0, .pipe = 1},
  {.name = "wc", .ptrToFunction = (uint64_t) &wc, .args = 0, .pipe = 0},
  {.name = "tron", .ptrToFunction = (uint64_t) &tron, .args = 0, .pipe = 0},
  {.name = "test-mm", .ptrToFunction = (uint64_t) &test_mm, .args = 0, .pipe = 0},
  {.name = "test-prio", .ptrToFunction = (uint64_t) &test_prio, .args = 0, .pipe = 0},
  {.name = "test-process", .ptrToFunction = (uint64_t) &test_processes, .args = 1, .pipe = 0}
};


int parseCommand(char ** command, char readBuf[BUFFER_LENGTH]) {
	int i = 0, commandWords = 0;
	
	for(int postSpace = 1; commandWords < MAX_COMMAND_WORDS && readBuf[i] != '\n' && readBuf[i] != 0; i++) {
    if(readBuf[i] == ' ') {
      postSpace = 1;
      readBuf[i] = 0;
    } else if(postSpace) {
      command[commandWords++] = readBuf + i; 
      postSpace = 0;
    }
	}

  readBuf[i] = 0;
  return commandWords;
}

unsigned int check_valid_program(char * string){
    for(int i = 0; i < PROGRAMS_QTY; i++){
        if(strcmp(string, programs[i].name)==0){
            return i;
        }
    }
    return -1;
}

char ** make_params(char ** words, unsigned int len){
    void * coso = (void*) sys_alloc((2 + len) * sizeof(char *)); // + 1 for name, + 1 por null termination

    if(coso == NULL){
        printf(MALLOC_ERROR);     //TODO: replace
        return NULL;
    }

    char ** params = (char **) coso;

    void * param;
    int paramLen;

    int i=0;
    for(; i<len + 1; i++){
        paramLen = strlen(words[i]) + 1;
        param = (void*) sys_alloc(paramLen);

         if(param == NULL){
            printf(MALLOC_ERROR);     //TODO: replace
            return NULL;
        }

        char * param2 = (char *) param;

        strncpy(param2, words[i], paramLen);
        params[i] = param2;
    }
    params[i] = NULL;

    return params;
}

int piped_process_handle(char ** words, unsigned int amount_of_words){
    if(amount_of_words != 3 || strcmp(PIPE, words[1]) != 0)
        return 0;
    unsigned int p1 = check_valid_program(words[0]);
    unsigned int p2 = check_valid_program(words[2]);
    if(p1 == -1 || p2 == -1){
        printf(INVALID_COMMAND_MSG);
        return 1;
    }
    if(!programs[p1].pipe){
        printf(PIPE_ERROR);
        return 1;
    }
    int pipe_id = sys_register_pipe_available();

    if(pipe_id <= 0){
        printf("Error creating pipe!");
        return 1;
    }

    sys_register_child_process(programs[p1].ptrToFunction, STDIN, pipe_id, (uint64_t) make_params(words, 0)); 
    sys_register_child_process(programs[p2].ptrToFunction, pipe_id, FOREGROUND, (uint64_t) make_params(words, 0)); 

    sys_wait_for_children();

    sys_destroy_pipe(pipe_id);

    return 2;
}

void single_process_handle(char ** words, unsigned int amount_of_words){
    unsigned int program_pos = check_valid_program(words[0]);

    if(program_pos == -1){
        printf(INVALID_COMMAND_MSG);
        return;
    }
    if(amount_of_words - 1 < programs[program_pos].args){
        printf(MISSING_ARGS);
        return;
    }


    // Check if user wants to run program in background
    int i, backgroud = 0;
    for(i=programs[program_pos].args + 1; !backgroud && i<amount_of_words; i++){
        if(strcmp("//", words[i]) == 0){         // We consider the symbol as the last argument. All subsequent arguments will be ignored
            backgroud = 2;       
        }
        else if(strcmp("/", words[i]) == 0){         // We consider the symbol as the last argument. All subsequent arguments will be ignored
            backgroud = 1;       
        }
    }

    // Run in background
    if(backgroud == 2){
        sys_register_process(programs[program_pos].ptrToFunction, STDIN, BACKGROUND, (uint64_t) make_params(words, MIN(i-1,programs[program_pos].args))); 
    }
    else if(backgroud == 1){
        sys_register_process(programs[program_pos].ptrToFunction, STDIN, FOREGROUND, (uint64_t) make_params(words, MIN(i-1,programs[program_pos].args))); 
    }

    // Run on screen
    else{
        sys_register_child_process(programs[program_pos].ptrToFunction, STDIN, FOREGROUND,  (uint64_t) make_params(words, MIN(amount_of_words-1, programs[program_pos].args))); 
        sys_wait_for_children();
    }
    
}

void shell() {
  print("Welcome to Shell! Type \"HELP\" for a list of commands.\n\n", 55);
  char * command[MAX_COMMAND_WORDS] = {0};

  while(1) {
    print(NEW_LINE, strlen(NEW_LINE));
    char readBuffer[BUFFER_LENGTH] = {0};
    scanf(readBuffer, BUFFER_LENGTH);

    int commandWords = parseCommand(command, readBuffer);

    if(commandWords == 0)
      continue;

    if(piped_process_handle(command,commandWords) == 0){
      single_process_handle(command,commandWords);
    }

  }
}