#include "main.h"
#include "utils.h"



int runExecutables(char **args);
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

	char *com = strdup(args[0]);
	strLower(com);

	if (strcmp(com, "cd") == 0)
	{
		cd(args);
	}
	
	else if ((strncmp(com, "#", 1) != 0))
	{
		runExecutables(args);
	}
		
	free(com);
	free(args);
	return 0;
}



/**
 * Forks process and then makes the child execute the command contained in args
 *
 * @param	args		an array of strings, null terminated
 * @return	int			0 for success
 */
int forkAndExecute(char **args)
{
	pid_t cpid;

	if ((cpid = fork()) == 0)
	{
		execvp(args[0], args);
		perror("msh");
		fprintf(stderr, "msh: cannot run %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		int cstat;
		wait(&cstat);
	}
	return 0;
}



/**
 * execs to command in args
 *
 * @param	args		an array of strings, null terminated
 * @return	int			-1 for failure
 */
int onlyExecute(char **args)
{

	execvp(args[0], args);
	fprintf(stderr, "msh: cannot run %s\n", args[0]);
	exit(EXIT_FAILURE);
	return -1;
}



/**
 * checks array of strings (that is NULL terminated) to determine if pipe characters '|' are present.
 * It then recursively goes through each pipe until the final NULL value is found. 
 *
 * @param	args	array of strings, null terminated
 * @return	int		0 for success
 */
int runExecutables(char **args)
//TODO: check why theres an fgets failure
			// is this affecting the fgets in main.c?
{
	int pfd1[2];
	int pfd2[2];
	pipe(pfd1);
	pipe(pfd2);
	bool isPiped = false;

	int pipeIndex = 0;
	pid_t cpid;

	int i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '|')
		{
			args[i] = NULL;
			
			if ((cpid = fork()) == 0)
			{
				//pipe stuff
				dup2(pfd1[1], STDOUT_FILENO);
				close(pfd1[0]);
				if (isPiped)
				{
					dup2(pfd2[0], STDIN_FILENO);
					close(pfd2[1]);
				}

				onlyExecute(&args[pipeIndex]);
			}
			else
			{
				dup2(pfd1[0], STDIN_FILENO);	//do i need stdin?
				close(pfd1[1]);
				if (isPiped)
				{
					dup2(pfd2[1], STDOUT_FILENO);
					close(pfd2[0]);
					isPiped = true;
				}

				int cstat;
				wait(&cstat);
			}
			pipeIndex = i + 1;
		}
		i++;
	}
	//TODO: check hwo this works out with the piping
	forkAndExecute(&args[pipeIndex]);	// runs final command when the NULL terminator has been found, 
										// this should run all commands that dont include pipes or the
										// last command after the last pipe char 
	close(pfd1[0]);
	if (isPiped)
	{
		close(pfd2[1]);
	}
	else
	{
		close(pfd2[1]);
		close(pfd2[0]);
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
		path = malloc(sizeof(char) * (strlen(homePath) + strlen(trimmedPath)));
		sprintf(path, "%s%s", homePath, trimmedPath); 
		free(trimmedPath);
		//need to free path
	}
	else 
	{
		path = args[1];
	}

	if (chdir(path) != 0)
	{
		perror("cd");
		if (args[1][0] == '~') free(path);
		return -1;
	}
	return 0;
}

