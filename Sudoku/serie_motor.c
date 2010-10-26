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


int found_value(struct cell** board, int side, int line, int col, int value){
	int k, n, l=sqrt(side);
	
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
	int i, j, *vec, k;
	int acc[side];
	
	/*** ROW ***/
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
			//printf("%d-%d\n", j, acc[j]);
			if (acc[j]==1) {
				for (k=0; k<side; k++) {
					if (is_possible_value(&board[i][k], j+1)) {
						found_value(board, side, i, k, j+1);
					}
				}
			}
		}
//		printf("\n\n");
	}
	
	/*** COL ***/
	for (i=0; i<side; i++) {
		for (j=0; j<side; j++) {
			acc[j]=0;
		}
		for (j=0; j<side; j++) {

			if (get_possibles(&board[j][i])) {
				vec = get_possibles_list(&board[j][i]);
				for (k=0; k<side; k++) {
					acc[vec[k]-1]++;
				}
			}
		}
		for (j=0; j<side; j++) {
			//printf("%d-%d\n", j+1, acc[j]);
			if (acc[j]==1) {
				for (k=0; k<side; k++) {
					if (is_possible_value(&board[k][i], j+1)) {
						found_value(board, side, k, i, j+1);
					}
				}
			}
		}
//		printf("\n");
	}
	
	/***************FAZER PARA OS QUADRADOS******************/
	
	return 0;
}


int solve_sudoku(struct cell** board, int side){
	int l = sqrt(side);
	int i, j;
	
	singleton(board, side);
	
	
	return 0;
}





























