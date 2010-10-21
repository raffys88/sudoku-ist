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
		position->possibles = 0;
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

	return 0;
}