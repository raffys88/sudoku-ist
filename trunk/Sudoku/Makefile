CC = gcc
CFLAGS = -Ansi -Wall

build: sudoku.c messages.h cell.c serie_motor.c
	$(CC) $(CCFLAGS) -o sudoku sudoku.c messages.h cell.c serie_motor.c
	
run: build
	./sudoku board.txt 
	
	
	
	
	
	
	> result.txt


all: clear build run
	
clear:
	clear
	
myne: clear build

run_valgrind:
	valgrind ./sudoku board.txt

valgrind: clear build run_valgrind 
