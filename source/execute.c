#include "main.h"
#include "utils.h"


int runExecutable(char **args);
char **splitCommand(char *command);
int cd(char **args);



/**
 * Interprets a command and does command if doable
 * 
 * @param	command		A string containing the inputted command,
 *						assumed to be "cleaned"
 * @return 	int			A value indicating result of command
 */
int interpret(char *command) 
{
	//split command into an array of strings thats null terminated
	char **args = splitCommand(command);

	//is command builtin?
		//check builtin list
		//run if there	
		char *com = strdup(args[0]);
		strLower(com);

		if (strcmp(com, "cd") == 0)
		{
			cd(args);
		}
		else
		{
			runExecutable(args);
		}
		
	free(com);
	free(args);
	return 0;
}



/**
 * Runs a given command line
 *
 * @param	command		A string holding the command
 * @return	int			An int identifying success (0) or fail (non 0);
 */
int runExecutable(char **args)
//assumes only 1 eternal command present, ie no piping.
{
	pid_t cpid;
	if ((cpid = fork()) == 0)
	{
		//this is the child
		execvp(args[0], args);
		fprintf(stderr, "msh: cannot run %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		int cstat;
		wait(&cstat);
		//check error and report
	}
	
	return 0;
}



/**
 * Splits a line of commands into an array of strings containing each space
 *  separated word. NOTE this separates on ALL spaces
 *
 * @param	command		String holding the whole command and its args
 * @return 	array		Sn array of strings containing 1 word each]
 */
char **splitCommand(char *command)
{
	char *com = strdup(command);
	int comBuff = SMLBUFF;
	char **comArgs = malloc(sizeof(char *) * comBuff);
	if (comArgs == NULL) 
	{
		perror("msh");
		return NULL;
	}

	int start = 0;
	int pos = 0;
	int c = 0;

	while (com[c] != '\0') 
	{
		if (isspace(com[c]) || com[c+1] == '\0') 
		{	
			if (isspace(com[c])) 
			{
				com[c] = '\0';
			}
			comArgs[pos] = &com[start];
			start = c + 1;
			pos++;
		}
		// need to grow arg array?
		if (pos + 1 >= comBuff) 
		{
			comBuff += SMLBUFF;
			comArgs = realloc(comArgs, sizeof(char *) * comBuff);
			if (comArgs == NULL) 
			{
				exit(EXIT_FAILURE);
			}
		}
		c++;
	}
	comArgs[pos] = NULL;
	return comArgs; 
}



/**
 * Builtin command that changes the programs working directory
 * 
 * @param	args	An array of strings containing the command sent to the shell.
 * @return	int		An in indicating success (0) or fail (-1)
 */
int cd(char **args)
{
	char *homePath = getenv("HOME");

	//// check for errors or expansions
	//check if theres too many args
	if (args[2] != NULL)
	{
		fprintf(stderr, "cd: incorrect number of arguments\n");
		return -1;
	}
	//no args means go home
	else if (args[1] == NULL)
	{
		if (chdir(homePath) != 0) 
		{
			perror("cd");
			return -1;
		}
		else return 0;
	}
	//expand tilde to homePath
	char *path;
	if (args[1][0] == '~')
	{
//something wrong in this block
		//expand home path
		char *trimmedPath = getSubstring(args[1], 1, strlen(args[1]));
		sprintf(path, "%s%s", homePath, trimmedPath); // i think problem is here
		printf("path now is %s\n", path);
		free(trimmedPath);
	}
	else 
	{
		path = args[1];
	}

	if (chdir(path) != 0)
	{
		perror("cd");
		return -1;
	}
	return 0;
}

