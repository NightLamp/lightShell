

#Vars
C99 = cc -std=c99
CFLAGS = -Wall -pedantic 
OBJECTS = input.o utils.o execute.o 

msh : main.o
	$(C99) $(CFLAGS) -o msh main.c $(OBJECTS)

main.o : main.h  main.c input.o execute.o 
	$(C99) $(CFLAGS) -c -o main.o main.c

input.o : main.h input.c utils.o
	$(C99) $(CFLAGS) -c -o input.o input.c

execute.o : main.h execute.c 
	$(C99) $(CFLAGS) -c -o execute.o execute.c

utils.o : utils.c
	$(C99) $(CFLAGS) -c -o utils.o utils.c

clean :
	rm -f *.o
