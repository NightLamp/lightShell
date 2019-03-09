#include "main.h"
#include "utils.h"



int pipeExecuatbles(char **args);
int pipeExecBounded(char **args, int bound, int outpfd);
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
	//var decs


	pipeExecBounded(args, 5, -1);
/*	
	//assume theres a command before and after '|'
	for (int i = 0; args[i] != NULL; i++)
	{
		//when a pipe command is found:
		if (args[i][0] == '|') 
		{
			
			
		}
	}
*/
	return 0;
}



/**
 * runs a piped execution and pipes output though a pipe. designed to be used 
 * recursively in the pipeExecutables function
 *
 * @param	args	array of strings. NULL terminated
 * @param	bound	the index to stop at. assumed that args[bound] == NULL
 * @param 	outpfd	pipe file descriptor to put output into, if -1 then wont pipe output
 * @return	int		0 for succ
 */
int pipeExecBounded(char **args, int bound, int outpfd) 
{
	//var decs
	int pDex = 0;
	int pCnt = 0;
	int stat;
	
	pid_t c1;
	pid_t c2;

	//run up to the bound
	for (int i = 0; i < bound; i++)
	{
		if (args[i][0] == '|')
		{
			pDex = i;
			pCnt++;
		}
	}
	//pipe works	
	int pfd[2];
	pipe(pfd);

	//switch the '|' with NULL so can use args and bound
	args[pDex] = NULL;

	//if theres more than one '|' then recurse into this function 
	if (pCnt > 1)
	{
		//piping

		pipeExecBounded(args, pDex, pfd[1]);
	}
	//else run the singular command left at the start	
	else if ((c1 = fork()) == 0)
	{
		//piping	
	
		onlyExecute(args);
	}
	waitpid(c1, &stat, 0);

	//always run last command
	if ((c2 =fork()) == 0)
	{
		//pipe Works

		onlyExecute(&args[pDex+1]);
	}
	waitpid(c2, &stat, 0);
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

