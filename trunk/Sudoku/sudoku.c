#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "serie_motor.h"
#include "messages.h"

struct cell** board;



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


int create_board(FILE* input_file){
	char read_char, *aux;
	int l, side=0, i = 0, j = 0, value;
	
	while(1){
		read_char = (char) getc(input_file);
		if(is_white_space(read_char))
			continue;
		if (read_char == EOF)
			return;
		break;
	}
	
	l = (int) strtol(&read_char, &aux, 10);
	
	side = l * l;
	
	board = (cell_ptr*) calloc(side, sizeof(cell_ptr));
	
	for(i=0; i<side; i++){
		board[i] = (cell_ptr) calloc(side, sizeof(struct cell));
		for (j=0; j<side;j++){
			create_cell(&board[i][j], side);
		}
	}
	return side;
}


void init_board(FILE* input_file, int side){
	int i=0, j=0, value=0, k, n, l = sqrt(side);
	char read_char, *aux;
	
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			
			while(1){
				read_char = getc(input_file);
				if(is_white_space(read_char))
					continue;
				if (read_char == EOF)
					return;
				break;
			}
			value = (int) strtol(&read_char, &aux, 10);
//			printf("%d ", value);
			
			if (value) {
				found_value(board, side, i, j, value);
				
			}
		}
//		printf("\n");
	}
}



void print_board(int side){
	int i=0, j=0;
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			printf("%d ", get_value(&board[i][j]));
		}
		printf("\n");
	}
}


void print_possibles_board(int side){
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
    int side = 0;
	const char* filename = argv[1];
	FILE* input_file;
	
	
	input_file = input_file = fopen(filename, "r");
	if (!input_file){
		perror(EFILE);
		return 1;
	}
	
	side = create_board(input_file);
	
	init_board(input_file, side);
	
	//print_possibles_board(side);
	
	solve_sudoku(board, side);
	
	//print_possibles_board(side);
	
	print_board(side);
	
	
	return 0;
}
