
#define BUFFSIZE 1024
#define SMLBUFF 124

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


extern int interpret(char *command);
extern int getCommand(char *buffer);


extern char *strdup(char *str);
extern char *strndup(char *str, int bound);
