/*
 *  serie_motor.c
 *  Sudoku
 *
 *  Created by Rui Boazinha on 10/19/10.
 *  Copyright 2010 IST. All rights reserved.
 *
 */

#include "serie_motor.h"
#include <math.h>
#include <stdio.h>

int flag=0;



int found_value(struct cell** board, int side, int line, int col, int value){
	int k, n, l=sqrt(side);
	if (flag) {
//		printf("FOUND_VALUE (%d,%d) %d\n", line+1, col+1, value);
	}
	set_value(&board[line][col], value);
	
	for (k=0; k<side; k++) {
		delete_possible(&board[k][col], value, side);
		delete_possible(&board[line][k], value, side);
	}
	
	int hoffset=(line*l)/side, voffset=(col*l)/side;
	
	for (k=0; k<l; k++) {
		for (n=0; n<l; n++) {
			delete_possible(&board[k+hoffset*l][n+voffset*l],value, side);
		}
	}
	return 0;
}

int alone(struct cell** board, int side){
	int dif=0, i, j, k;
		for (i=0; i<side; ++i) {
			for (j=0; j<side; ++j) {
				if ((board[i][j].possibles)==1) {
					for (k=0; k<side; ++k) {
						if (board[i][j].possible[k]) {
							dif = 1;
							found_value(board, side, i, j, board[i][j].possible[k]);
							break;
						}
					}
				}
			}
		}
	return dif;
}


int singleton(struct cell** board, int side){
	int i, j, k, n, x, m, acc, val;
	int l = sqrt(side);
	//int acc[side];
	int* line[side];
	int* colu[side];
	int* square[side];
	int ret =0;
	
	
//	printf("LINE\n\n");
	for (k=0; k<side; ++k) {
		for (i=0; i<side; ++i) {
			line[i] = board[k][i].possible;
		}
		
		for (j=0; j<side; ++j) {
			acc=0;
			val=-1;
			for (i=0; i<side; ++i) {
				if ((line[i]!=NULL) && (line[i][j] == (j+1))) {
					++acc;
					val=i;
				}
			}
			if (acc == 1) {
//				printf("SINGLETON (%d,%d) %d\n", k+1, val+1, j+1);
				found_value(board, side, k, val, j+1);
				++ret;
			}
		}
	}
	
	
//	printf("\nCOL\n\n");

	for (k=0; k<side; ++k) {
		for (i=0; i<side; ++i) {
			colu[i] = board[i][k].possible;
		}
		
		for (j=0; j<side; ++j) {
			acc=0;
			val=-1;
			for (i=0; i<side; ++i) {
				if ((colu[i]!=NULL) && (colu[i][j] == (j+1))) {
					++acc;
					val=i;
				}
			}
			if (acc == 1) {
//				printf("SINGLETON (%d,%d) %d\n", val+1, k+1, j+1);
				found_value(board, side, val, k, j+1);
				++ret;
			}
		}
		
	}
	
	
	
//	printf("\nSQUARE\n\n");
	
	for (n=0; n<l; ++n) {
		int	voffset=n*l;
		for (x=0; x<l; ++x) {
			int hoffset =x*l;
			
			m=0;
			for (i=0; i<l; ++i) {
				for (j=0; j<l; ++j) {
					square[m++] = board[i+voffset][j+hoffset].possible;
				}
			}
			
			
			
			
			for (j=0; j<side; ++j) {
				acc=0;
				val=-1;
				for (i=0; i<side; ++i) {
					if ((square[i]!=NULL) && (square[i][j] == (j+1))){
						++acc;
						val=i;
					}
				}
				
				if (acc == 1) {
					
//					printf("SINGLETON (%d,%d) %d\n", voffset + val/l +1, 1+hoffset+val%l, j+1);
					found_value(board, side, voffset + val/l, hoffset+val%l, j+1);
					++ret;
				}
			}
			
			
			
			
			
			
		}
	}
	
	return ret;
}


int check_solution(struct cell** board, int side){
	int i, j, x, k, n, aux, l=sqrt(side);
	int acc[side];
	
	
	//ROW
	for (k=0; k < side; ++k) {
		
		for (i=0; i<side; ++i) {
			acc[i]=0;
		}
		
		for (i=0; i < side; ++i) {
			if ((aux = get_value(&board[k][i]))) {
				acc[aux-1]++;}
			else{
				return 2;}
		}
		
		for (i=0; i<side; ++i) {
			if (acc[i] != 1) {
				return 1;
			}
		}
		
		
	}
	
	//COLUMN
	for (k=0; k<side; ++k) {
		for (i=0; i<side; ++i) {
			acc[i]=0;
		}
		
		for (i=0; i<side; ++i) {
			if ((aux = get_value(&board[i][k]))) {
				acc[aux-1]++;}
			else{
				return 2;}
			
		}
		
		for (i=0; i<side; ++i) {
			if (acc[i] != 1) {
				return 1;
			}
		}
		
	}
	
	//SQUARE
	for (n=0; n<l; ++n) {
		int	voffset=n*l;
		for (x=0; x<l; ++x) {
			int hoffset =x*l;
			
			for (i=0; i<side; ++i) {
				acc[i]=0;
			}
			
			for (i=0; i<l; ++i) {
				for (j=0; j<l; ++j) {
					if ((aux = get_value(&board[i+voffset][j+hoffset]))) {
						acc[aux-1]++;}
					else{
						return 2;}
				}
			}
			
			for (i=0; i<side; ++i) {
				if (acc[i] != 1) {
					return 1;
				}
			}
		}
	}
	
	return 0;
}


int solve_sudoku(struct cell** board, int side){
	int i;
	flag =1;
	for (i=0; i<10; ++i) {
		while (alone(board, side)){}
		while (singleton(board, side)){}
	}
	
	switch (check_solution(board, side)) {
		case 0:
			printf("OK\n");
			break;
		case 1:
			printf("ERRORS\n");
			break;
		case 2:
			printf("MISSES\n");
			break;
		default:
			break;
	}
	
	
	
	return 0;
}





























