/**
 Project:	lightshell

 file: 	lightshell.c
 By: 	NightLamp

**/


#include "lightshell.h"



int main(int argc, char * argv[]) {

	char command[BUFFSIZE];

	int limit = 0;

	do {
		printf("$: ");
		getCommand(command);

		printf("you gave me: %s\n", command);

		doCommand(command);
	
		limit++;
	}
	while (limit < 4 && (strcmp(command, "exit") != 0));
	
	exit(EXIT_SUCCESS);
}
