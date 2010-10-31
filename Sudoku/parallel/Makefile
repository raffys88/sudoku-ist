CC = gcc
CFLAGS = -Ansi -Wall


build: sudoku.c cell.c serie_motor.c 
	$(CC) $(CCFLAGS) -o sudoku sudoku.c cell.c serie_motor.c 

	
build_check:
	$(CC) $(CCFLAGS) -o ../check ../check.c
	

	
run: clear run_1 run_2 run_3 run_4 run_5 run_7 run_8 run_9 run_10

	
clear:
	clear
	

	
run_1: build build_check
	./sudoku ../tests/1-2x2.txt > ../result.txt
	../check 2 < ../result.txt

run_2: build build_check
	./sudoku ../tests/2-3x3.txt > ../result.txt
	../check 3 < ../result.txt
	
run_3: build build_check
	./sudoku ../tests/3-4x4.txt > ../result.txt
	../check 4 < ../result.txt
	
run_4: build build_check
	./sudoku ../tests/4-5x5.txt > ../result.txt
	../check 5 < ../result.txt
	
run_5: build build_check
	./sudoku ../tests/5-8x8.txt > ../result.txt
	../check 8 < ../result.txt
	
run_6: build build_check
	./sudoku ../tests/6-9x9.txt > ../result.txt
	../check 9 < ../result.txt
	
run_7: build build_check
	./sudoku ../tests/7-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_8: build build_check
	./sudoku ../tests/8-10x10.txt > ../result.txt
	../check 10 < ../result.txt
	
run_9: build build_check
	./sudoku ../tests/9-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_10: build build_check
	./sudoku ../tests/10-4x4.txt > ../result.txt
	../check 4 < ../result.txt

run_11: build build_check
	./sudoku ../tests/11-6x6.txt > ../result.txt
	../check 6 < ../result.txt
