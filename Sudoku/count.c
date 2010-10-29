/*
 *  untitled.c
 *  Sudoku
 *
 *  Created by Rui Boazinha on 10/28/10.
 *  Copyright 2010 IST. All rights reserved.
 *
 */

#include<stdio.h>




int main (int argc, const char * argv[]) {
    int acc = 0;
	char c;
	const char* filename = argv[1];
	FILE* input_file;
	
	
	input_file = fopen(filename, "r");
	
	
	
	while ((c = getc(input_file)) != EOF) {
		
		if (c=='0') {
			++acc;
		}
	}
	
	
	
	fclose(input_file);

	
	printf("ZEROS %d\n", acc);
	return 0;
}