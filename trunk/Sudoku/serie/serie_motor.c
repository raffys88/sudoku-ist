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
#include <stdlib.h>


sudoku_board create_board(int side){
	int i = 0, j = 0;
	sudoku_board board = (sudoku_board) calloc(side, sizeof(cell_ptr));
	
	for(i=0; i<side; i++){
		board[i] = (cell_ptr) calloc(side, sizeof(struct cell));
		for (j=0; j<side;j++){
			create_cell(&board[i][j], side);
		}
	}
	return board;
}


void delete_board(sudoku_board board, int side){
	int i, j;
	
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			delete_cell(&board[i][j], side);
		}
		free(board[i]);
	}
	free(board);
}


int possible_value(sudoku_board board, int side, int row, int column, int value){
	int i, j, l=sqrt(side);
	
	if (board[row][column].possible[value-1]==0) {
		return 0;
	}
	
	// ROW & COLUMN
	for (i=0; i < side; ++i) { 
		if ((value == get_value(&board[row][i])))
			return 0;
		if ((value == get_value(&board[i][column]))) 
			return 0;
	}
	
	//SQUARE
	int	voffset=row/l;
	int hoffset =column/l;
	
	for (i=0; i<l; ++i) {
		for (j=0; j<l; ++j) {
			if ((value == get_value(&board[i+voffset*l][j+hoffset*l]))) 
				return 0;
		}
	}
	
	return 1;
}


int check_solution(sudoku_board board, int side){
	int i, j, x, k, n, aux, l=sqrt(side);
	int acc[side];
	
	
	//ROW
	for (k=0; k < side; ++k) {
		
		for (i=0; i<side; ++i) {
			acc[i]=0;
		}
		
		for (i=0; i < side; ++i) {
			if ((aux = get_value(&board[k][i]))) {
				acc[aux-1]++;}
			else{
				return 2;}
		}
		
		for (i=0; i<side; ++i) {
			if (acc[i] != 1) {
				return 1;
			}
		}
		
		
	}
	
	//COLUMN
	for (k=0; k<side; ++k) {
		for (i=0; i<side; ++i) {
			acc[i]=0;
		}
		
		for (i=0; i<side; ++i) {
			if ((aux = get_value(&board[i][k]))) {
				acc[aux-1]++;}
			else{
				return 2;}
			
		}
		
		for (i=0; i<side; ++i) {
			if (acc[i] != 1) {
				return 1;
			}
		}
		
	}
	
	//SQUARE
	for (n=0; n<l; ++n) {
		int	voffset=n*l;
		for (x=0; x<l; ++x) {
			int hoffset =x*l;
			
			for (i=0; i<side; ++i) {
				acc[i]=0;
			}
			
			for (i=0; i<l; ++i) {
				for (j=0; j<l; ++j) {
					if ((aux = get_value(&board[i+voffset][j+hoffset]))) {
						acc[aux-1]++;}
					else{
						return 2;}
				}
			}
			
			for (i=0; i<side; ++i) {
				if (acc[i] != 1) {
					return 1;
				}
			}
		}
	}
	
	return 0;
}


int found_value(sudoku_board board, int side, int line, int col, int value){
	int k, n, l=sqrt(side);
	
	set_value(&board[line][col], side, value);
	
	for (k=0; k<side; k++) {
		delete_possible(&board[k][col], value, side);
		delete_possible(&board[line][k], value, side);
	}
	
	int hoffset=(line*l)/side, voffset=(col*l)/side;
	
	for (k=0; k<l; k++) {
		for (n=0; n<l; n++) {
			delete_possible(&board[k+hoffset*l][n+voffset*l],value, side);
		}
	}
	return 0;
}


int alone(sudoku_board board, int side){
	int dif=0, i, j, k;
	for (i=0; i<side; ++i) {
		for (j=0; j<side; ++j) {
			if ((board[i][j].possibles)==1) {
				for (k=0; k<side; ++k) {
					if (board[i][j].possible[k]) {
						dif = 1;
						found_value(board, side, i, j, board[i][j].possible[k]);
						break;
					}
				}
			}
		}
	}
	return dif;
}


int singleton(sudoku_board board, int side, int row1, int column1, int row2, int column2){
	int i, j, k, n, x, m, acc, val;
	int l = sqrt(side);
	int* line[side];
	int* colu[side];
	int* square[side];
	int ret =0;
	
	
	//	printf("LINE\n\n");
	for (k=row1; k<row2; ++k) {
		
		for (i=0; i<side; ++i) {
			line[i] = board[k][i].possible;
		}
		
		for (j=0; j<side; ++j) {
			acc=0;
			val=-1;
			for (i=0; i<side; ++i)
				if ((line[i]!=NULL) && (line[i][j] == (j+1))) {
					++acc;
					val=i;
				}
			
			if (acc == 1) {
				found_value(board, side, k, val, j+1);
				++ret;
			}
		}
	}
	
	
	//	printf("\nCOL\n\n");
	for (k=column1; k<column2; ++k) {
		
		for (i=0; i<side; ++i) {
			colu[i] = board[i][k].possible;
		}
		
		for (j=0; j<side; ++j) {
			acc=0;
			val=-1;
			for (i=0; i<side; ++i)
				if ((colu[i]!=NULL) && (colu[i][j] == (j+1))) {
					++acc;
					val=i;
				}
			if (acc == 1) {
				found_value(board, side, val, k, j+1);
				++ret;
			}
		}
	}
	
	//	printf("\nSQUARE\n\n");
	if (row1+1==row2 && column1+1==column2) {
		
		int	voffset = row1/l;
		int hoffset = column1/l;
		
		m=0;
		for (i=0; i<l; ++i)
			for (j=0; j<l; ++j)
				square[m++] = board[i+voffset][j+hoffset].possible;
		
		for (j=0; j<side; ++j) {
			acc=0;
			val=-1;
			for (i=0; i<side; ++i)
				if ((square[i]!=NULL) && (square[i][j] == (j+1))){
					++acc;
					val=i;
				}
			if (acc == 1) {
				found_value(board, side, voffset + val/l, hoffset+val%l, j+1);
				++ret;
			}
		}
		
	}
	else {
		for (n=0; n<l; ++n) {
			int	voffset = n*l;
			for (x=0; x<l; ++x) {
				int hoffset = x*l;
				
				m=0;
				for (i=0; i<l; ++i)
					for (j=0; j<l; ++j)
						square[m++] = board[i+voffset][j+hoffset].possible;
				
				for (j=0; j<side; ++j) {
					acc=0;
					val=-1;
					for (i=0; i<side; ++i)
						if ((square[i]!=NULL) && (square[i][j] == (j+1))){
							++acc;
							val=i;
						}
					if (acc == 1) {
						found_value(board, side, voffset + val/l, hoffset+val%l, j+1);
						++ret;
					}
				}
			}
		}
	}

	
	return ret;
}


int pairs(sudoku_board board, int side, int row1, int column1, int row2, int column2){
	int i, j, k, n, m, alt=0, l=sqrt(side), voffset, hoffset;
	struct cell* squares[side];
	
	//COLUMN
	for (k=column1; k<column2; ++k) 
		for (i=0; i<side; ++i) 
			if (get_possibles(&board[i][k])==2) 
				for (j=i+1; j<side; ++j) 
					if ((get_possibles(&board[j][k]))==2) 
						if (equals_possibles(&board[i][k], &board[j][k], side)) 
							for (n=0; n<side; n++) 
								if ((n!=i) && (n!=j))
									for (m=0; m<side; ++m) 
										if (board[j][k].possible[m]) 
											alt += delete_possible(&board[n][k], board[j][k].possible[m], side);
	
	//ROW
	for (k=row1; k<row2; ++k) 
		for (i=0; i<side; ++i)
			if (get_possibles(&board[k][i])==2) 
				for (j=i+1; j<side; ++j) 
					if ((get_possibles(&board[k][j]))==2) 
						if (equals_possibles(&board[k][i], &board[k][j], side)) 
							for (n=0; n<side; n++) 
								if ((n!=i) && (n!=j))
									for (m=0; m<side; ++m) 
										if (board[k][j].possible[m]) 
											alt += delete_possible(&board[k][n], board[k][j].possible[m], side);
	
	
	//SQUARES
	if (row1+1==row2 && column1+1==column2) {
		
		int	voffset = row1/l;
		int hoffset = column1/l;
		
		k=0;
		for (i=0; i<l; ++i)
			for (j=0; j<l; ++j)
				squares[k++]=&board[i+voffset*l][j+hoffset*l];
		for (i=0; i<side; ++i){
			if (get_possibles(squares[i])==2) 
				for (j=i+1; j<side; ++j) 
					if ((get_possibles(squares[j]))==2) 
						if (equals_possibles(squares[i], squares[j], side)) 
							for (n=0; n<side; n++) 
								if ((n!=i) && (n!=j))
									for (m=0; m<side; ++m) 
										if (squares[j]->possible[m]) 
											alt += delete_possible(squares[n], squares[j]->possible[m], side);
		}
		
	}
	else {
		for (n=0; n<l; ++n)
			for (m=0; m<l; ++m) {
				voffset = n/l;
				hoffset = m/l;
				k=0;
				for (i=0; i<l; ++i)
					for (j=0; j<l; ++j)
						squares[k++]=&board[i+voffset*l][j+hoffset*l];
				for (i=0; i<side; ++i){
					if (get_possibles(squares[i])==2) 
						for (j=i+1; j<side; ++j) 
							if ((get_possibles(squares[j]))==2) 
								if (equals_possibles(squares[i], squares[j], side)) 
									for (n=0; n<side; n++) 
										if ((n!=i) && (n!=j))
											for (m=0; m<side; ++m) 
												if (squares[j]->possible[m]) 
													alt += delete_possible(squares[n], squares[j]->possible[m], side);
				}
				
			}
	}
	return alt;
}


int bad_possible_elimination(sudoku_board board, int side){
	int i, j, k, n, m,aa=0, abc, alone_ok=0;
	sudoku_board test_board;
	//	print_board(board, side);
	
	for (i=0; i<side; ++i) {//ROW
		for (j=0; j<side; ++j) {//COLUMN
			//printf("row=%d  column=%d\n", i, j);
			//printf("\tvalue = %d\n", get_value(&board[i][j]));
			if (get_value(&board[i][j])==0) {
				for (k=0; k<side; ++k) {//POSSIBLE
					//printf("k=%d   possible=%d\n", k, board[i][j].possible[k]);
					if (board[i][j].possible[k]){
						test_board = create_board(side);
						for (n=0; n<side; ++n) 
							for (m=0; m<side; ++m){
								if (get_value(&board[n][m])) 
									found_value(test_board, side, n, m, get_value(&board[n][m]));
							}
						found_value(test_board, side, i, j, board[i][j].possible[k]);
						
						alone_ok=0;
						for (n=0; n<side; ++n) {
							if ((board[i][n].possibles)==1) {
								for (m=0; m<side; ++m) {
									if (board[i][n].possible[m]) {
										alone_ok = 1;
										found_value(test_board, side, i, n, board[i][n].possible[m]);
									}
								}
							}
							if ((board[n][j].possibles)==1) {
								for (m=0; m<side; ++m) {
									if (board[n][j].possible[m]) {
										alone_ok = 1;
										found_value(test_board, side, n, j, board[n][j].possible[m]);
									}
								}
							}
						}
						if (singleton(test_board, side, i, j, i+1, j+1))
							alone_ok = 1;
						if (pairs(test_board, side, i, j, i+1, j+1))
							alone_ok = 1;
						
						if (alone_ok) {
							while (1){
								if (alone(board, side))
									continue;

								if (singleton(board, side, 0, 0, side, side))
									continue;
								
								if (pairs(board, side, 0, 0, side, side))
									continue;
								break;
							}
						}
						
						
						
						abc = check_solution(test_board, side);
						//printf("%d\n", aa);
						switch (abc) {
							case 0:
								found_value(board, side, i, j, board[i][j].possible[k]);
								delete_board(test_board, side);
								return -1;
							case 1:
								delete_possible(&board[i][j], board[i][j].possible[k], side);
								++aa;
								break;
							default:
								break;
						}
						delete_board(test_board, side);
					}
				}
			}
		}
	}
	
	
	return aa;
}


int next(sudoku_board board, int side, int row, int column){
	if (row == (side-1) && column == (side-1)){
		return check_solution(board, side);
	}
	if(column == (side-1)){
		return recursive_solution(board, side, row+1, 0);
	}
	else {
		return recursive_solution(board, side, row, column+1);
	}
}


int recursive_solution(sudoku_board board, int side, int row, int column){
	int i=0, test, ret;
	
	
	//	char aux;
	//print_board(side);
	//printf("row= %d  column=%d\n", row+1, column+1);
	//	scanf("%c", &aux);
	
	
	
	test = check_solution(board, side);
	//printf("test= %d\n", test);
	
	if (test == 0) {
		//VALID BOARD
		//printf("\t1-VALID BOARD\n");
		return 0;
	}
	else{
		//ERRORS FOUND IN BOARD
		//printf("\t2-INVALID BORRD\n");
		if (get_value(&board[row][column])) {
			//printf("\t\t3-FILLED WITH %d\n",board[row][column].value);
			return next(board, side, row, column);
		}
		else {
			//printf("\t\t4-NOT FILLED \n");
			for (i=0; i < side; ++i) {
				//printf("\t\t\ti= %d\n",i+1);
				//printf("\t\t\tpossible?= %d\n",possible_value(board, side, row, column, i+1));
				if (possible_value(board, side, row, column, i+1)) {
					//printf("\t\t\t\tTRY i= %d \n", i+1);
					try_value(&board[row][column], i+1);
					ret = next(board, side, row, column);
					//printf("\t\t\t\tNEXT RETURN= %d \n", ret);
					if (ret) {
						//printf("\t\t\t\t\t7-CONTINUE\n");	
						continue;
					}
					else {
						//printf("\t\t\t\t\t6-OK BOARD FOUND\n");	
						return 0;
					}
					
				}
				else {
					//printf("\t\t\t\t5-IMPOSSIBLE i=%d \n", i+1);
					continue;
				}
			}
			//printf("\t\t8- ALL TRIED AND FAIL PREVEW \n");
			try_value(&board[row][column], 0);
			return 1;
		}
		return 1;
	}
	return 0;
}


int solve_sudoku(sudoku_board board, int side){
	int i=0;
	
	while (1){
		//printf("\tALONE\n");
		if (alone(board, side))
			continue;
		if (check_solution(board, side)==0)
			break;
		//printf("\t\tSINGLETON\n");
		if (singleton(board, side, 0, 0, side, side))
			continue;
		if (check_solution(board, side)==0)
			break;
		//printf("\t\t\tPAIRS\n");
		if (pairs(board, side, 0, 0, side, side))
			continue;
		if (check_solution(board, side)==0)
			break;
		//print_board(board, side);
		//printf("\t\t\t\tBAD POSSIBLE\n");
		i=bad_possible_elimination(board, side);
		//printf(" %d\n", i);
		if(i)
			continue;
		if (check_solution(board, side)==0)
			break;
		//printf("\t\t\t\t\tRECURSIVE\n");
		recursive_solution(board, side, 0, 0);
		break;
	}
	
	/*switch (check_solution(board, side)) {
		case 0:
			printf("\n--OK--\n");
			break;
		case 1:
			printf("\n--ERRORS--\n");
			break;
		case 2:
			printf("\n--MISSES--\n");
			break;
		default:
			break;
	}*/
	return 0;
}





























