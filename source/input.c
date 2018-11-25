
#include "main.h"



/**
 Gets the next command written to the shell. This is a blocking function.

 @param		buffer	a string that will be filled with the new command.

 @return	int		1 for success
					0 for fail
**/
int getCommand(char *buffer) 
{
	if (fgets(buffer, BUFFSIZE, stdin) == NULL) 
	{
		//line read failure
		fprintf(stderr, "fgets failure\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		int commandLen = strlen(buffer);
		buffer[commandLen-1] = '\0';	//remove newline

		return 1;
	}
}
