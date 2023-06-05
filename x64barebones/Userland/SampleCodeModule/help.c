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
  "kill                 Given a pid, its process is terminated\n"
  "loop                 Prints its pid every 0.2 seconds following a greeting\n"
  "mem                  Prints memory status\n"
  "nice                 Given a pid and a new priority, changes priority of process\n"
  "phylo                Implements phylosophers problem\n"
  "                     With 'a' you add a phylo, with 'r' you remove a phylo and with 'q' you quit the program\n"
  "printmem             Given an address pointer prints the following 32 bytes\n"
	"ps                   Shows every running process and it's state\n"
  "time                 Prints the current time\n"
  "wc                   Returns new lines quantity\n"
  "\n"
	"tron                 Play Tron!\n"
  "------------ TESTS ------------\n"
  "test-mm              Tests memory manager\n"
  "test-process         Given a number test scheduling based on that amount of programs\n"
  "test-prio            Tests pipes and semaphores\n"
  "test-sync            Tests pipes and semaphores. Try with 1 (for semaphores) or 0 (without semaphores) as parameter\n";


void help() {
	print(helpString, strlen(helpString));
}