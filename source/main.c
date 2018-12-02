
#include "main.h"
#include "utils.h"

int main(int argc, char * argv[]) 
{
	char command[BUFFSIZE];
	strcpy(command, "");	//ensures that command doesnt start with exit
	
	//command loop
	while (1)
	{
		//print prompt
			//get USER, PCNAME, CWD, and if SU or not etc
		printf("USER@PC CWD $: ");

		//get input
		getCommand(command);

		//parse input

		
		//is it exit?
		strLower(command);
		if (strcmp("exit", command) == 0) return 0;

		//command execution
		interpret(command);

		//Set up for next command
	}
}
