#include <commands.h>
#include <functions.h>
#include <shell.h>

const char* helpString = 
  "block                Given a pid changes that process state to blocked\n"
  "cat                  Prints stdin as received\n"
  "clear                Clears screen's content\n"
	"changefontsize       Given a number between 1 and 3 as a parameter it changes the font size\n"
	"divbyzero            Simulates the error that occurs when dividing by zero\n"
  "filter               Filters vowels on input\n"
	"help                 Prints all commands and their description\n"
	"inforeg              Prints the value of the registers when screenshotted. Use ESCAPE to screenshot\n"
	"invalidopcode        Simulates the error that occurs when using an invalid operation code\n"
  "phylo                Implements phylosophers problem\n"
  "printmem             Given an address pointer prints the following 32 bytes\n"
	"ps                   Shows every running process and it's state\n"
  "mem                  Prints memory status\n"
  "nice                 Given a pid changes priority of process\n"
	"loop                 Given a number prints its pid every that amount of seconds\n"
	"kill                 Given a pid a process is ended\n"
  "phylo                Runs the philosofers program\n"
  "                     With 'a' you add a phylo, with 'r' you remove a phylo and with 'q' you quit the program\n"
  "filter               Filters vocals\n"
	"time                 Prints the current time\n"
	"tron                 Executes the game tron light cycle\n"
  "test-mm              Tests memory manager\n"
  "test-process         Given a number test scheduling based on that amount of programs\n"
  "test-prio            Tests pipes and semaphores\n";

void help() {
	print(helpString, strlen(helpString));
}