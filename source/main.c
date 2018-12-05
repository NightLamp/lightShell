
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
		normaliseSpaces(command);
		
		//is it exit?
		char *temp = strndup(command, 4); 
		strLower(temp);
		if (strcmp("exit", temp) == 0) 
		{
			return 0;
		}
		free(temp);
		
		//command execution
		interpret(command);

		//Set up for next command
	}
}
