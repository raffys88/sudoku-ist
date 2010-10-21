CC = gcc
CFLAGS = -Ansi -Wall

build: sudoku.c messages.h cell.h
	$(CC) $(CCFLAGS) -o sudoku sudoku.c messages.h cell.c
	
run: build
	./sudoku board.txt


all: build run
	