CC = gcc
CFLAGS = -Ansi -Wall

build: sudoku.c messages.h cell.c serie_motor.c
	$(CC) $(CCFLAGS) -o sudoku sudoku.c messages.h cell.c serie_motor.c
	
run: build
	./sudoku board.txt


all: clear build run
	
clear:
	clear
	
myne: clear build