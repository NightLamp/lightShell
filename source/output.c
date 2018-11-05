/**
 Project:	lightshell

 file: 	output.c
 By: 	NightLamp

**/


#include "lightshell.h"



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



char **splitCommand(char **command) {

	char *com = *command;

	int comBuff = SMOLBUFF;
	char **comArgs = malloc(sizeof(char *) * comBuff);

	int start = 0;
	int pos = 0;

	int c = 0;


	while (com[c] != '\0') {

		if (isspace(com[c]) || com[c+1] == '\0') {
			
			if (isspace(com[c])) {
				com[c] = '\0';
			}
			comArgs[pos] = &com[start];
			start = c + 1;
			pos++;
		}
		// need to grow arg array?
		if (pos + 1 >= comBuff) {	//+1 for null at end.
			comBuff += SMOLBUFF;
			comArgs = realloc(comArgs, sizeof(char *) * comBuff);
			if (comArgs == NULL) {
				exit(EXIT_FAILURE);
			}
		}
		c++;
	}

	comArgs[pos] = NULL;
	return comArgs; 

}




//should be 'normalised' first. .ie no extra spaces/tabs

int commandToArgvOld(char *command, char ***comArgv) {


	*comArgv = malloc(100);
	char **argv = *comArgv;
	argv[0] = command;
	return 0;
}

/*
	int wordStart = 0;
	int wordSize = 0;

	int spaces = 0;
	int c = 0;

	//split commands
	while (command[c] != '\0') {

		if (isspace(command[c])) {

			if (c - wordStart > wordSize) {wordSize = c - wordStart;}
			wordStart = c;

			spaces++;
			command[c] = '\0';
		}
		c++;
	}
	
	c = 0;

	//set up memory
	*comArgv = malloc( sizeof(char) * (spaces + 1) * wordSize);
	char **argv = *comArgv;
	int wordCount = 0;

	while (wordCount < spaces) {

		argv[wordCount] = command;
		
		int wordLen = strlen(command);
		c = wordLen;
		wordCount++;
	}

	return 0;
} */



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





