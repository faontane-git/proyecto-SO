FUNC = csapp.o csapp.h
CC = gcc
FLAGS = -O2 -Wall -I . -o
LIB = -lpthread

merge: cliente.o $(FUNC)
	$(CC) $(FLAGS) chasquiEats cliente.o csapp.o $(LIB)

cliente.o: cliente.c
	gcc -c cliente.c
	
csapp.o: csapp.c
	gcc -c csapp.c
	
.PHONY: debug clean All


All:
	 

clean:
	rm *.o merge
	
debug: mergeSort.c csapp.c
	$(CC) -g $(FLAGS) merge mergeSort.c $(LIB)
	gdb ./merge