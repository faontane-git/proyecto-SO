FUNC = csapp.o csapp.h
CC = gcc
FLAGS = -O2 -Wall -I . -o 
LIB = -lpthread -lm

merge: chasquiEats.o $(FUNC)
	$(CC) $(FLAGS) chasquiEats chasquiEats.o csapp.o $(LIB)

chasquiEats.o: chasquiEats.c
	gcc -c chasquiEats.c
	
csapp.o: csapp.c
	gcc -c csapp.c
	
.PHONY: debug clean All


All:
	 

clean:
	rm *.o merge
	
 