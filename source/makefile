#Makefile for lish


#Vars
C99 = cc -std=c99
CFLAGS = -Wall -pedantic 
OBJECTS = input.o output.o utils.o

lish : lightshell.o
	$(C99) $(CFLAGS) -o lish lightshell.c $(OBJECTS)

lightshell.o : lightshell.h  lightshell.c input.o output.o
	$(C99) $(CFLAGS) -c -o lightshell.o lightshell.c

input.o : lightshell.h input.c utils.o
	$(C99) $(CFLAGS) -c -o input.o input.c 


output.o : lightshell.h output.c utils.o
	$(C99) $(CFLAGS) -c -o output.o output.c

utils.o : lightshell.h utils.c
	$(C99) $(CFLAGS) -c -o utils.o utils.c

clean :
	rm -f *.o
