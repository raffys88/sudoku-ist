/*
 *  cell.c
 *  Sudoku
 *
 *  Created by Rui Boazinha on 10/20/10.
 *  Copyright 2010 IST. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "cell.h"

int create_cell(cell_ptr position, int value, int side){
	int i = 0, j = 0;
	
	if (value){
		
		position->value = value;
		position->possibles = j;
		position->possible = NULL;
	}
	else {
		
		position->possible = (int*) calloc(side-1, sizeof(int*));
		position->value = value;
		position->possibles = j;
		
		for (i = 1; i <= side; i++) {
			
			if (value != i){
				position->possible[j] = i;
				++j;
			}
		}
		position->possibles = j;
	}
	position->possibles_orig = j;

	return 0;
}

int get_value(cell_ptr position){
	return position->value;
}

int is_possible_value(cell_ptr position, int value){
	int i;
	for (i=0; i < position->possibles; ++i) {
		if (position->possible[i] == value) {
			return 1;
		}
	}
	
	return 0;
}

int get_final(cell_ptr position){
	return 0;
}