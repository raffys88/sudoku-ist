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
#include <math.h>

#include "cell.h"

int create_cell(cell_ptr position, int side){
	int i = 0;
	position->possible = (int*) calloc(side, sizeof(int*));
	position->value = 0;
	position->possibles = side;
	
	for (i = 0; i < side; i++) {
		position->possible[i] = i+1;
	}
	
	return 0;
}

void delete_cell(cell_ptr position, int side){
	free(position->possible);
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

int get_possibles(cell_ptr position){
	return position->possibles;
}



int set_value(cell_ptr position, int side, int value){
	int i;
	position->value = value;
	position->possibles=0;
	for (i=0; i<side; ++i) {
		position->possible[i]=0;
	}
	return 0;
}


int try_value(cell_ptr position, int value){
	position->value = value;
	return 0;
}



int delete_possible(cell_ptr position, int value,int side){
	int i ,alt=0;
	if (position->possibles < 1) {
		return 0;
	}
	for (i=0; i<side; i++) {
		
		if (position->possible[i] == value) {
			alt=1;
			position->possible[i] = 0;
			position->possibles-=1;
			return position->possibles;
		}
	}
	
	return alt;
}


int get_first_possible(cell_ptr position, int side){
	int i = 0;
	
	for (i=0; i<side; i++) {
		if (position->possible[i]) {
			return position->possible[i];
		}
	}
	
	return 0;
}



int* get_possibles_list(cell_ptr position){
	return position->possible;
}




int equals_possibles(cell_ptr one_position, cell_ptr two_position, int side){
	int i;
	
	for (i=0; i<side; ++i) {
		if ((one_position->possible[i]) != (two_position->possible[i]))  {
			return 0;
		}
	}
	return 1;
}


