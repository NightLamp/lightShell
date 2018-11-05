#Makefile for lish


#Vars
C99 = cc -std=c99
CFLAGS = -Wall -pedantic 
OBJECTS = input.o execute.o utils.o commands.o

lish : lightshell.o
	$(C99) $(CFLAGS) -o lish lightshell.c $(OBJECTS)

lightshell.o : lightshell.h  lightshell.c input.o execute.o commands.o
	$(C99) $(CFLAGS) -c -o lightshell.o lightshell.c

input.o : lightshell.h input.c utils.o
	$(C99) $(CFLAGS) -c -o input.o input.c 

commands.o : lightshell.h commands.c execute.o
	$(C99) $(CFLAGS) -c -o commands.o commands.c

execute.o : lightshell.h execute.c utils.o
	$(C99) $(CFLAGS) -c -o execute.o execute.c

utils.o : lightshell.h utils.c
	$(C99) $(CFLAGS) -c -o utils.o utils.c

clean :
	rm -f *.o
