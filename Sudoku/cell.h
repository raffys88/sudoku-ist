/*
 *  cell.h
 *  Sudoku
 *
 *  Created by Rui Boazinha on 10/20/10.
 *  Copyright 2010 IST. All rights reserved.
 *
 */
 

#ifndef CELL_H
#define CELL_H


typedef struct cell{
	int value;
	int possibles;
	int* possible;
}* cell_ptr;


int create_cell(cell_ptr position, int side);


int get_value(cell_ptr position);


int is_possible_value(cell_ptr position, int value);


int get_final(cell_ptr position);


int set_value(cell_ptr position, int value);


int delete_possible(cell_ptr position, int value, int side);

#endif