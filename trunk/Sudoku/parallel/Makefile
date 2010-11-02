CC = gcc
CFLAGS =  -Wall -fopenmp 


build: clear build_cell build_motor build_check
	$(CC) $(CFLAGS) -fopenmp -o sudoku-omp sudoku-omp.c cell.o motor.o 


build_motor: build_cell
	$(CC) $(CFLAGS) -o motor.o -c omp_motor.c


build_cell:
	$(CC) $(CFLAGS) -o cell.o -c cell.c

	
build_check:
	$(CC) -o ../check ../check.c

	
clear:
	clear

	
run: clear run_1 run_2 run_3 run_4 run_5 run_7 run_8 run_9 run_10
	

	
run_1: build 
	time ./sudoku-omp ../tests/1-2x2.txt > ../result.txt
	../check 2 < ../result.txt

run_2: build 
	time ./sudoku-omp ../tests/2-3x3.txt > ../result.txt
	../check 3 < ../result.txt
	
run_3: build 
	time ./sudoku-omp ../tests/3-4x4.txt > ../result.txt
	../check 4 < ../result.txt
	
run_4: build 
	time ./sudoku-omp ../tests/4-5x5.txt > ../result.txt
	../check 5 < ../result.txt
	
run_5: build build_check
	time ./sudoku-omp ../tests/5-8x8.txt > ../result.txt
	../check 8 < ../result.txt
	
run_6: build 
	time ./sudoku-omp ../tests/6-9x9.txt > ../result.txt
	../check 9 < ../result.txt
	
run_7: build 
	time ./sudoku-omp ../tests/7-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_8: build 
	time ./sudoku-omp ../tests/8-10x10.txt > ../result.txt
	../check 10 < ../result.txt
	
run_9: build 
	time ./sudoku-omp ../tests/9-3x3.txt > ../result.txt
	../check 3 < ../result.txt

run_10: build 
	time ./sudoku-omp ../tests/10-4x4.txt > ../result.txt
	../check 4 < ../result.txt

run_11: build 
	time ./sudoku-omp ../tests/11-6x6.txt > ../result.txt
	../check 6 < ../result.txt
