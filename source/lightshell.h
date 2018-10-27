/**
 Project:	lightshell

 file: 	lightshell.h
 By: 	NightLamp

**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// preprocessor constants
#define BUFFSIZE 1024

// prototypes
	//input.c
	extern int getCommand(char *buffer);
	//output.c
	extern int doCommand(char *command);
	extern int commandToArgv(char *command, char ***comArgv);
	//utils.c
	extern char *getSubstring(char *str, int start, int end);

