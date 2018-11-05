

#include "lightshell.h"


int changeDirectory(char *path) {

	if (chdir(path) != 0) {

		fprintf(stderr, "cd error\n");	//needs to check error status to see why
		return -1;
	}		
	return 0;
}


int doCommand(char *command) {

	//normalise commands

	//check inbuilt commands
	if (strncmp(command, "cd", 2) == 0) {

		char *path = getSubstring(command, 3, strlen(command) );
		changeDirectory(path);
		free(path);
	}
	//run other commands
	else {

		execCommand(command);
	}
	return 0;
}


int execCommand(char *command) {

	char **cArgv = splitCommand(&command);
	
	// Child:
	if (fork() == 0) {

		if (execvp(cArgv[0], cArgv) == -1) {
			fprintf(stderr,"lish: command execute error\n");
			exit(EXIT_FAILURE);
		}
	} 

	// Parent
	else {
		free(cArgv);
		wait(0);
	}
	
	return 0;
}

