#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "serie_motor.h"
#include "messages.h"


struct cell **board;


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

int read_board(FILE* input_file){
	char read_char, *aux;
	int l, side=0, i = 0, j = 0, value;
	
	read_char = (char) fgetc(input_file);
	
	l = (int) strtol(&read_char, &aux, 10);
	
	side = l * l;
	
	board = (cell_ptr*) calloc(side, sizeof(cell_ptr));
	
	for(i=0; i<side; i++){
		board[i] = (cell_ptr) calloc(side, sizeof(struct cell));
		for (j=0; j<side;j++){
			while(1){
				read_char = getc(input_file);
				if(is_white_space(read_char))
					continue;
				if (read_char == EOF)
					break;
				break;
			}
			value = (int) strtol(&read_char, &aux, 10);
			printf("%d ", value);
			
			create_cell(&board[i][j], value, side);
			
		}
		printf("\n");		
	}
	printf("\n\n\n\n\n\n\n\n\n");
	return side;
}


void print_board(int side){
	int i=0, j=0;
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			printf("%d ", board[i][j].value);
		}
		printf("\n");
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
	
	side = read_board(input_file);
	
	
	print_board(side);
	
	
	return 0;
}
