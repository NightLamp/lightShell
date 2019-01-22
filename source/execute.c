#include "main.h"
#include "utils.h"



int pipeExecuatbles(char **args);
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
		pipeExecuatbles(args);
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
int pipeExecuatbles(char **args)
{
	int pfd[2];
	bool isPiped = false;
	int pipeIndex = 0;
	pid_t cpid;

	pipe(pfd);		

	int i = 0;
	while (args[i] != NULL)
	{

		if (args[i][0] == '|' || args[i+1] == NULL)
		{
			printf("command to be run: %s\n", args[pipeIndex]);

			// check if we are here from pipe symbol
			if (args[i+1] != NULL) 
			{
				args[i] = NULL;	
			}			

			//child
			if ((cpid = fork()) == 0)
			{
				//if youre noy at the end or you are and have piped before:
				if (args[i+1] != NULL || isPiped)
				{
					// dont send final output through pipe
					if (args[i+1] != NULL)
					{
						dup2(pfd[1], STDOUT_FILENO);
						close(pfd[1]);
					}
					else
					{
						close(pfd[1]);
					}
					
					//only get input from stdin if there was a command before
					if (isPiped)
					{
						dup2(pfd[0], STDIN_FILENO);
						close(pfd[0]);
					}
					else
					{
						close(pfd[0]);
					}
				}
				else
				{
					close(pfd[0]);
					close(pfd[1]);
				}	
	
				onlyExecute(&args[pipeIndex]);
			}

			//parent
			else
			{
				//close pipe when you get to teh last command
				if (args[i+1] == NULL)
				{
					close(pfd[0]);
					close(pfd[1]);
				}

				int cstat;
				wait(&cstat);
			}
			pipeIndex = i+1;	//offset by 1 so the index starts at command after the |
			isPiped = true;
		}
		i++;
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

