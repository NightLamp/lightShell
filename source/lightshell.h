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
#define SMOLBUFF 64

// prototypes
	//input.c
	extern int getCommand(char *buffer);
	//commands.c	
	extern int changeDirectory(char *path);
	extern int execCommand(char *command);
	extern int doCommand(char *command);
	//execute.c
	extern char **splitCommand(char **command);
	extern int commandToArgvOld(char *command, char ***comArgv);
	//utils.c
	extern char *getSubstring(char *str, int start, int end);

