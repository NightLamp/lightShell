
#include "main.h"
#include "utils.h"


int main(int argc, char * argv[]) 
{
	char command[BUFFSIZE];
	strcpy(command, "");	//ensures that command doesnt start with exit
	

	char *user;
	char hostname[_SC_HOST_NAME_MAX];
	char thecwd[BUFFSIZE]; 

	//command loop
	while (1)
	{
		user = getlogin(); //better to use getpwuid(geteuid()) for safety	
		gethostname(hostname, _SC_HOST_NAME_MAX);
		getcwd(thecwd, BUFFSIZE);

		//print prompt
			//TODO: get if SU or not 
		printf("%s@%s %s $: ", user, hostname, thecwd);

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
