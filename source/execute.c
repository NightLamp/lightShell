
#include "myShell.h"



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
