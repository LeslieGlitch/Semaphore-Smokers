# Variables to control Makefile operation
CC = g++
CFLAGS1 = -Wall -g -c
CFLAGS2 = -g

.PHONY: clean

# User actions
run: main
	./main

clean:
	rm -f main *.o

# Link object files together
main: main.o
	${CC} ${CFLAGS2} -o main main.o

# Compile each file to an object
main.o: main.cpp
	${CC} ${CFLAGS1} -o main.o main.cpp
