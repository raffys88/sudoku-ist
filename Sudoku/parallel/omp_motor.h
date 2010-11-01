/*
 *  serie_motor.h
 *  Sudoku
 *
 *  Created by Rui Boazinha on 10/19/10.
 *  Copyright 2010 IST. All rights reserved.
 *
 */

#ifndef SERIE_MOTOR_H
#define SERIE_MOTOR_H

#include "cell.h"

typedef cell_ptr* sudoku_board;



sudoku_board create_board(int side);

void delete_board(sudoku_board board, int side);

int possible_value(sudoku_board board, int side, int row, int column, int value);


int found_value(sudoku_board board, int side, int line, int col, int value);


int solve_sudoku(sudoku_board board, int side);


int recursive_solution(sudoku_board board, int side, int row, int column);


#endif