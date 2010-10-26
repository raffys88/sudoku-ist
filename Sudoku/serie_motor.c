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
		printf("FOUND_VALUE (%d,%d) %d\n", line+1, col+1, value);
	}
	set_value(&board[line][col], value);
	
	for (k=0; k<side; k++) {
		
		if(delete_possible(&board[k][col], value, side) == 1)
			found_value(board, side, k, col, get_first_possible(&board[k][col], side));
		
		if(delete_possible(&board[line][k], value, side) == 1)
			found_value(board, side, line, k, get_first_possible(&board[line][k], side));
	}
	
	int hoffset=(line*l)/side, voffset=(col*l)/side;
	
	for (k=0; k<l; k++) {
		for (n=0; n<l; n++) {
			if (delete_possible(&board[k+hoffset*l][n+voffset*l],value, side) == 1) {
				found_value(board, side, k+hoffset*l, n+voffset*l, get_first_possible(&board[k+hoffset*l][n+voffset*l], side));
			}
		}
	}
	return 0;
}

int singleton(struct cell** board, int side){
	int i, j, *vec, k, n, x, acc, val;
	int l = sqrt(side);
	//int acc[side];
	int* line[side];
	int* colu[side];
	int* square[side];
	
	print_possibles_board(side);
	
	
	printf("LINE\n\n");
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
				printf("SINGLETON (%d,%d) %d\n", k+1, val+1, j+1);
			//	found_value(board, side, k, val, j+1);
			}
		}
	}
	
	
	printf("\nCOL\n\n");
	
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
				printf("SINGLETON (%d,%d) %d\n", val+1, k+1, j+1);
				//found_value(board, side, val, k, j+1);
			}
		}
		
	}
	
	printf("\nSQUARE\n\n");
	
	for (n=0; n<l; ++n) {
		int	voffset=n*l;
		for (x=0; x<l; ++x) {
			int hoffset =x*l;
			
			
			for (i=0; i<l; ++i) {
				for (j=0; j<l; ++j) {
					square[i+j] = board[i+voffset][j+hoffset].possible;
					
				}
			}
			
			
			
			for (j=0; j<side; ++j) {
				acc=0;
				val=-1;
				for (i=0; i<side; ++i) {
					if ((square[i]!=NULL) && (square[i][j] == (j+1))) {
						++acc;
						val=i;
					}
				}
				if (acc == 1) {
					
					//printf("SINGLETON (%d,%d) %d\n", voffset + val/l, hoffset+val%l, j+1);
					//found_value(board, side, val, k, j+1);
				}
			}
			
			
			
			
			
			
		}
	}
	
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			if (square[i]) 
				printf("%d ", square[i][j]);
			else {
				printf("- ");
			}

		}
		printf("\n");
	}
	
	
	
	
	
	/*printf("------------------------------------------------------------------------------------row\n");
	/*** ROW ***
	 for (i=0; i<side; i++) {
	 for (j=0; j<side; j++) {
	 acc[j]=0;
	 }
	 for (j=0; j<side; j++) {
	 if (get_possibles(&board[i][j])) {
	 vec = get_possibles_list(&board[i][j]);
	 for (k=0; k<side; k++) {
	 acc[vec[k]-1]++;
	 }
	 }
	 }
	 for (j=0; j<side; j++) {
	 
	 if (acc[j]==1) {
	 for (k=0; k<side; k++) {
	 if (is_possible_value(&board[i][k], j+1)) {
	 //						printf("(%d,%d) %d\n", i+1, k+1, j+1);
	 found_value(board, side, i, k, j+1);
	 }
	 }
	 }
	 }
	 }
	 printf("------------------------------------------------------------------------------------col\n");
	 print_possibles_board(side);
	 /*** COL **
	 for (i=0; i<side; i++) {
	 
	 for (j=0; j<side; j++) {
	 acc[j]=0;
	 }
	 for (j=0; j<side; j++) {
	 //			printf("col%d line%d----------------------------------\n",i+1, j+1);
	 //			printf("\tpossibles=%d\n", get_possibles(&board[j][i]));
	 if (get_possibles(&board[j][i])) {
	 vec = get_possibles_list(&board[j][i]);
	 //				printf("\tvec=");
	 for (k=0; k<side; k++) {
	 //					printf("%d ", vec[k]);
	 if (vec[k]) {
	 acc[vec[k]-1]++;
	 }
	 }
	 }
	 //			printf("\n\tACC=");
	 //			for (k=0; k<side; ++k) {
	 //				printf("(%d,%d) ", k+1, acc[k]);
	 //			}
	 //			printf("\n--------------------------------------------\n\n");
	 }
	 
	 for (j=0; j<side; j++) {
	 
	 if (acc[j]==1) {
	 for (k=0; k<side; k++) {
	 if (is_possible_value(&board[k][i], j+1)) {
	 printf("SINGLETON (%d,%d) %d\n", k+1, i+1, j+1);
	 found_value(board, side, i, k, j+1);
	 break;
	 }
	 }
	 }
	 }
	 }
	 
	 printf("------------------------------------------------------------------------------------square\n");
	 /***************SQUARE******************
	 for (k=0; k<l; k++) {
	 const int voffset = k*l;
	 for (n=0; n<l; n++) {
	 const int hoffset = n*l;
	 for (i=0; i<side; i++) {
	 acc[i]=0;
	 }
	 
	 for (i=0; i<l; i++) {
	 for (j=0; j<l; j++) {
	 //			print_possibles_board(side);
	 //			printf("i=%d   j=%d\n", i, j);
	 //			printf("(%d,%d) ",i+voffset+1, j+hoffset+1);
	 //			printf("get_possibles=%d\n", get_possibles(&board[i+voffset][j+hoffset]));
	 
	 
	 if (get_possibles(&board[i+voffset][j+hoffset]) > 0) {
	 
	 for (x=0; x<side; x++) {
	 if (board[i+voffset][j+hoffset].possible[x]) {
	 acc[(board[i+voffset][j+hoffset].possible[x])-1]++;
	 //						printf("5\n");
	 }
	 }
	 //				printf("6\n");
	 }
	 
	 }
	 //		printf("\n");
	 }
	 
	 for (x=0; x<side; x++) {
	 if (acc[x]==1) {
	 for (i=0; i<side; ++i) {
	 for (j=0; j<l; ++j) {
	 
	 if (is_possible_value(&board[i+voffset][j+hoffset], j+1)) {
	 //						printf("FOUND (%d,%d) %d\n", i+voffset, j+hoffset, j+1);
	 found_value(board, side, i+voffset, j+hoffset, j+1);
	 }
	 }
	 }
	 }
	 }
	 }
	 printf("\n");
	 }*/
	
	//print_board(side);
	
	
	return 0;
}


int solve_sudoku(struct cell** board, int side){
	int l = sqrt(side);
	int i, j;
	flag =1;
	singleton(board, side);
	
	
	return 0;
}





























