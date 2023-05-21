#include <commands.h>
#include <functions.h>

const char* helpString = 
  "clear           							Clears screen's content\n"
	"changefontsize    			  Given a number between 1 and 3 as a parameter it changes the font size\n"
	"divbyzero								      Simulates the error that occurs when dividing by zero.\n"
	"help				               Prints all commands and their description.\n"
	"inforeg						 				     Prints the value of the registers when screenshotted. Use ESCAPE to screenshot\n"
	"invalidopcode							   Simulates the error that occurs when using an invalid operation code.\n"
  "printmem							  		    Given an address pointer prints the following 32 bytes.\n"
	"time				               Prints the current time.\n"
	"tron				               Executes the game tron light cycle.\n";

void help() {
	print(helpString, strlen(helpString));
}