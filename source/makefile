#Makefile for lish


#Vars
C99 = cc -std=c99
CFLAGS = -Wall -pedantic 
OBJECTS = input.o execute.o utils.o commands.o

msh : myShell.o
	$(C99) $(CFLAGS) -o msh myShell.c $(OBJECTS)

myShell.o : myShell.h  myShell.c input.o execute.o commands.o
	$(C99) $(CFLAGS) -c -o myShell.o myShell.c

input.o : myShell.h input.c utils.o
	$(C99) $(CFLAGS) -c -o input.o input.c 

commands.o : myShell.h commands.c execute.o
	$(C99) $(CFLAGS) -c -o commands.o commands.c

execute.o : myShell.h execute.c utils.o
	$(C99) $(CFLAGS) -c -o execute.o execute.c

utils.o : myShell.h utils.c
	$(C99) $(CFLAGS) -c -o utils.o utils.c

clean :
	rm -f *.o
