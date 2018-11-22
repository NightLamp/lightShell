
#include "myShell.h"



int main(int argc, char * argv[]) {

	char command[BUFFSIZE];


	do {
		printf("$: ");
		getCommand(command);

		doCommand(command);
	}
	while (strcmp(command, "exit") != 0);
	
	exit(EXIT_SUCCESS);
}
