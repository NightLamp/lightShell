/**
 Project:	lightshell

 file: 	output.c
 By: 	NightLamp

**/


#include "lightshell.h"



int doCommand(char *command) {

	char **cArgv = NULL;
	commandToArgv(command, &cArgv);

	printf("command to be run: %s\n", cArgv[0]);

	//Child:
	if (fork() == 0) {

		execvp(cArgv[0], cArgv);
	} 

	//Parent
	else {
		//free(cArgv);
		wait(0);
	}
	
	return 0;
}



//should be 'normalised' first. .ie no extra spaces/tabs

int commandToArgv(char *command, char ***comArgv) {


	*comArgv = malloc(20);
	*comArgv[0] = "ls";


	return 0;
}



/*
	int spaces = 1;
	int c = 0;

	//replace spaces with nullbytes.
	while (command[c] != '\0') {

		printf("c2a[c] = %c\n", command[c]);
		if (isspace(command[c])) {

			command[c] = '\0';
			spaces++;
		}
		c++;
	}

	if (c <= 0) {
		fprintf(stderr, "empty command string\n");
	}
	c = 0;

	comArgv = malloc(sizeof(char *) * (spaces + 1));	// +1 for nullbyte at end
	int ca = 0;

	//populate comArgv
	while (ca < spaces) {

		comArgv[ca] = &command[c];

		c += strlen(&command[c] + 1);	//skip intermittent null bytes
		ca++;
	}
	if (ca == spaces) {
		comArgv[ca] = NULL;
	}
	return comArgv;

} */





