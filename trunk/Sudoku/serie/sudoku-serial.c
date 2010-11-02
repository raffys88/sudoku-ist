#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "serie_motor.h"





int is_white_space(char c){
	
	switch (c) {
		case ' ': return 1; break;
		case '\t': return 1; break;
		case '\n': return 1; break;
		case '\b': return 1; break;
		case '\f': return 1; break;
		case '\0': return 1; break;
		default: return 0;
			break;
	}
	
	return 0;
}


void init_board(sudoku_board board, FILE* input_file, int side){
	int i=0, j=0, value=0;
	
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			
			
			fscanf(input_file, "%d", &value);
//			printf("%d ", value);
			
			if (value) {
				found_value(board, side, i, j, value);
				
			}
		}
//		printf("\n");
	}
}


void print_board(sudoku_board board, int side){
	int i=0, j=0;
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			printf("%2d ", get_value(&board[i][j]));
		}
		printf("\n");
	}
}


void print_possibles_board(sudoku_board board, int side){
	int i=0, j=0, k;
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			printf("(%d)", board[i][j].possibles);
			for (k=0; k<side; k++){
				if(board[i][j].possible){
					if (board[i][j].possible[k]) {
						printf("%d", board[i][j].possible[k]);
					}
					else
						printf(".");
				}
				else {
					printf("-");
					//printf("%d", board[i][j].value);
				}
			}
			printf("  ");
		}
		printf("\n\n");
	}
	
}


int main (int argc, const char * argv[]) {
    int side = 0, l;
	const char* filename = argv[1];
	FILE* input_file;
	
	
	input_file = fopen(filename, "r");
	if (!input_file){
		perror("ERROR: Error on file opening.\n");
		return 1;
	}
		
	fscanf(input_file, "%d", &l);
	
	side = l*l;
	sudoku_board board = create_board(side);
	
	init_board(board, input_file, side);
	
	//print_possibles_board(side);
	
	solve_sudoku(board, side);
	
	//print_possibles_board(board, side);
	
	print_board(board, side);
	
	delete_board(board, side);
	
	return 0;
}
