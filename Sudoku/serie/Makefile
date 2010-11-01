CC = gcc
CFLAGS = -Wall 


build: clear build_cell build_motor build_check
	$(CC) $(CFLAGS) -o sudoku sudoku.c cell.o motor.o 


build_motor: build_cell
	$(CC) $(CFLAGS) -o motor.o -c serie_motor.c


build_cell:
	$(CC) $(CFLAGS) -c cell.c

	
build_check:
	$(CC) -o ../check ../check.c

	
clear:
	clear

	
run: clear run_1 run_2 run_3 run_4 run_5 run_7 run_8 run_9 run_10
	

	
run_1: build 
	./sudoku ../tests/1-2x2.txt > ../result.txt
	../check 2 < ../result.txt

run_2: build 
	./sudoku ../tests/2-3x3.txt > ../result.txt
	../check 3 < ../result.txt
	
run_3: build 
	./sudoku ../tests/3-4x4.txt > ../result.txt
	../check 4 < ../result.txt
	
run_4: build 
	./sudoku ../tests/4-5x5.txt > ../result.txt
	../check 5 < ../result.txt
	
run_5: build build_check
	./sudoku ../tests/5-8x8.txt > ../result.txt
	../check 8 < ../result.txt
	
run_6: build 
	./sudoku ../tests/6-9x9.txt > ../result.txt
	../check 9 < ../result.txt
	
run_7: build 
	./sudoku ../tests/7-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_8: build 
	./sudoku ../tests/8-10x10.txt > ../result.txt
	../check 10 < ../result.txt
	
run_9: build 
	./sudoku ../tests/9-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_10: build 
	./sudoku ../tests/10-4x4.txt > ../result.txt
	../check 4 < ../result.txt

run_11: build 
	./sudoku ../tests/11-6x6.txt > ../result.txt
	../check 6 < ../result.txt
