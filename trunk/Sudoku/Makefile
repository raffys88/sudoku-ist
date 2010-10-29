CC = gcc
CFLAGS = -Ansi -Wall

build: clear sudoku.c messages.h cell.c serie_motor.c
	$(CC) $(CCFLAGS) -Wall -o sudoku sudoku.c messages.h cell.c serie_motor.c
	
run: build
	./sudoku board.txt 
	> result.txt
	
run_all: build
	./sudoku 1-2x2.txt
	./sudoku 2-3x3.txt
	./sudoku 3-4x4.txt
	./sudoku 4-5x5.txt
	./sudoku 5-8x8.txt
	./sudoku 6-9x9.txt

valgrind: build 
	valgrind ./sudoku board.txt
	
clear:
	clear
	
	
run_1: build
	./sudoku 1-2x2.txt

run_2: build
	./sudoku 2-3x3.txt
	
run_3: build
	./sudoku 3-4x4.txt
	
run_4: build
	./sudoku 4-5x5.txt

run_5: build
	./sudoku 5-8x8.txt

run_6: build
	./sudoku 6-9x9.txt