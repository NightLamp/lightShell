
#include "main.h"



/**
 * Gets the next command written to the shell. This is a blocking function.
 *
 * @param	buffer	a string that will be filled with the new command.
 *
 * @return	int		1 for success
 *					0 for fail
 */
int getCommand(char *buffer) 
{
	if (fgets(buffer, BUFFSIZE, stdin) == NULL)	//line read failure
	{
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



/**
 * Removes excess whitespaces, leaving only 1 space in its place.
 *  
 * @param	str		string to be altered
 *
 * @return	int 	1 if success
					0 if failed
 */
int normaliseSpaces(char *str)
{
	//looks like it gets stuck after multiple spaces

	char temp[strlen(str)];
	int state = isspace(str[0]) ? 1 : 0;
	int j = 0; 

	for (int i = 0; str[i] != '\0'; i++)
	{
		//using a state machine
			//1 if prev wspace
			//0 if prev not wspace
		
		//if no space before and space now: add space to new string (s to 1)
		//if space before and space now: next (s to 1)
		//if no space before and no space now: next (s to 0)
		//if space before and no space now: next (s to 0)

		if (state == 0 && isspace(str[i]))		
		{
			temp[j++] = ' ';
			state = 1;
		}
		else if (isspace(str[i]) == 0)
		{
			temp[j++] = str[i];
			state = 0;
		}
	}

	temp[j] = '\0';

	if (strcpy(str, temp) == NULL) 
	{
		perror("msh: stringParsing");
		return -1;
	}
	else return 0;
}
