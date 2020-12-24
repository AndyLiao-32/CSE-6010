#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

#include "tictactoe.h"

/* rule 2*/

int get_xo_num_row(int *int_puzzle_arr, int nRows, int nCols, int *x_num_row, int *o_num_row, int still_empty) {
	// int *x_num_row, int *o_num_row are two arrays which stored the number of "X" & "O" for each row
	for(int i = 0; i < nRows; i++) {
		int count_x = 0;
		int count_o = 0;

		for(int j = 0; j < nCols; j++) {
			if (*(int_puzzle_arr + i * nCols + j) == 1) {
				count_x++;
			}
			if (*(int_puzzle_arr + i * nCols + j) == 2) {
				count_o++;
			}
		}
		// assigned the number of X in each row to "x_num_row"
		*(x_num_row + i) = count_x;
		still_empty -= count_x;
		*(o_num_row + i) = count_o;
		still_empty -= count_o;
	}

	return still_empty;
}

void get_xo_num_col(int *int_puzzle_arr, int nRows, int nCols, int *x_num_col, int *o_num_col) {
	for(int i = 0; i < nCols; i++) {
		int count_x = 0;
		int count_o = 0;

		for(int j = 0; j < nRows; j++) {
			if (*(int_puzzle_arr + j * nRows + i) == 1) {
				count_x++;
			}
			if (*(int_puzzle_arr + j * nRows + i) == 2) {
				count_o++;
			}
		}
		// assigned the number of X in each row to "x_num_row"
		*(x_num_col + i) = count_x;
		*(o_num_col + i) = count_o;
	}
}

void get_Q_index(int *int_puzzle_arr, int nRows, int nCols, int *q_index_row, int *q_index_col, int still_empty) {
	int a = 0;

	while(a < still_empty) {
		for(int i = 0; i < nRows; i++) {
			for(int j = 0; j < nCols; j++) {
				if (*(int_puzzle_arr + i * nCols + j) == 0) {
					*(q_index_row + a) = i;
					*(q_index_col + a) = j;
					a += 1;
				}
			}
		}
	}
}

int check_consecutive(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty) {
	// here we use N ecause nRows and nCols all equal to N
	for(int i = 0; i < N; i++) { 
		// check x_row
		if(*(x_num_row + i) >= 2) {
			for(int j = 0; j < nCols - 1; j++) {
				if((*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 1)) && (*(int_puzzle_arr + i * nCols + j) == 1)) {
					if(j == 0) {
						if (*(int_puzzle_arr + i * nCols + j + 2) != 2) {
							*(int_puzzle_arr + i * nCols + j + 2) = 2;
							printf("Now for row assigned 'O' (x, y) : (%d, %d) \n", i, j + 2);
							still_empty -= 1;
						}
					} else if(j == nCols - 2) {
						if (*(int_puzzle_arr + i * nCols + j - 1) != 2) {
							*(int_puzzle_arr + i * nCols + j - 1) = 2;
							printf("Now for row assigned 'O' (x, y) : (%d, %d) \n", i, j - 1);
							still_empty -= 1;
						}
					} else {
						if (*(int_puzzle_arr + i * nCols + j + 2) != 2) {
							*(int_puzzle_arr + i * nCols + j + 2) = 2;
							printf("Now for row assigned 'O' (x, y) : (%d, %d) \n", i, j + 2);
							still_empty -= 1;
						}
						if (*(int_puzzle_arr + i * nCols + j - 1) != 2) {
							*(int_puzzle_arr + i * nCols + j - 1) = 2;
							printf("Now for row assigned 'O' (x, y) : (%d, %d) \n", i, j - 1);
							still_empty -= 1;
						}
					}
				}
			}
		}

		// check o_row
		if(*(o_num_row + i) >= 2) {
			for(int j = 0; j < nCols - 1; j++) {
				if((*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 1)) && (*(int_puzzle_arr + i * nCols + j) == 2)) {
					if(j == 0) {
						if (*(int_puzzle_arr + i * nCols + j + 2) != 1) {
							*(int_puzzle_arr + i * nCols + j + 2) = 1;
							printf("Now for row assigned 'X' (x, y) : (%d, %d) \n", i, j + 2);
							still_empty -= 1;
						}
					} else if(j == nCols - 2) {
						if (*(int_puzzle_arr + i * nCols + j - 1) != 1) {
							*(int_puzzle_arr + i * nCols + j - 1) = 1;
							printf("Now for row assigned 'X' (x, y) : (%d, %d) \n", i, j - 1);
							still_empty -= 1;
						}
					} else {
						if (*(int_puzzle_arr + i * nCols + j + 2) != 1) {
							*(int_puzzle_arr + i * nCols + j + 2) = 1;
							printf("Now for row assigned 'X' (x, y) : (%d, %d) \n", i, j + 2);
							still_empty -= 1;
						}
						if (*(int_puzzle_arr + i * nCols + j - 1) != 1) {
							*(int_puzzle_arr + i * nCols + j - 1) = 1;
							printf("Now for row assigned 'X' (x, y) : (%d, %d) \n", i, j - 1);
							still_empty -= 1;
						}
					}
				}
			}
		}

		// check x_col
		if(*(x_num_col + i) >= 2) {
			for(int j = 0; j < nRows - 1; j++) {
				if((*(int_puzzle_arr + j * nRows + i) == *(int_puzzle_arr + (j + 1) * nRows + i)) && (*(int_puzzle_arr + j * nRows + i) == 1)) {
					if(j == 0) {
						// printf("check for the %d column_x\n", i);
						if (*(int_puzzle_arr + (j + 2) * nRows + i) != 2) {
							*(int_puzzle_arr + (j + 2) * nRows + i) = 2;
							printf("Now for col assigned 'O' (x, y) : (%d, %d) \n", j + 2, i);
							still_empty -= 1;
						}
					} else if(j == nCols - 2) {
						// printf("check for the %d column_x\n", i);
						if (*(int_puzzle_arr + (j - 1) * nRows + i) != 2) {
							*(int_puzzle_arr + (j - 1) * nRows + i) = 2;
							printf("Now for col assigned 'O' (x, y) : (%d, %d) \n", j - 1, i);
							still_empty -= 1;
						}
					} else {
						// printf("check for the %d column_x\n", i);
						if (*(int_puzzle_arr + (j + 2) * nRows + i) != 2) {
							*(int_puzzle_arr + (j + 2) * nRows + i) = 2;
							printf("Now for col assigned 'O' (x, y) : (%d, %d) \n", j + 2, i);
							still_empty -= 1;
						}
						if (*(int_puzzle_arr + (j - 1) * nRows + i) != 2) {
							*(int_puzzle_arr + (j - 1) * nRows + i) = 2;
							printf("Now for col assigned 'O' (x, y) : (%d, %d) \n", j - 1, i);
							still_empty -= 1;
						}
					}
				}
			}
		}

		// check o_col.
		if(*(o_num_col + i) >= 2) {
			for(int j = 0; j < nRows - 1; j++) {
				if((*(int_puzzle_arr + j * nRows + i) == *(int_puzzle_arr + (j + 1) * nRows + i)) && (*(int_puzzle_arr + j * nRows + i) == 2)) {
					if(j == 0) {
						if (*(int_puzzle_arr + (j + 2) * nRows + i) != 1) {
							*(int_puzzle_arr + (j + 2) * nRows + i) = 1;
							printf("Now for col assigned 'X' (x, y) : (%d, %d) \n", j + 2, i);
							still_empty -= 1;
						}
					} else if(j == nCols - 2) {
						if (*(int_puzzle_arr + (j - 1) * nRows + i) != 1) {
							*(int_puzzle_arr + (j - 1) * nRows + i) = 1;
							printf("Now for col assigned 'X' (x, y) : (%d, %d) \n", j - 1, i);
							still_empty -= 1;
						}
					} else {
						if (*(int_puzzle_arr + (j + 2) * nRows + i) != 1) {
							*(int_puzzle_arr + (j + 2) * nRows + i) = 1;
							printf("Now for col assigned 'X' (x, y) : (%d, %d) \n", j + 2, i);
							still_empty -= 1;
						}
						if (*(int_puzzle_arr + (j - 1) * nRows + i) != 1) {
							*(int_puzzle_arr + (j - 1) * nRows + i) = 1;
							printf("Now for col assigned 'X' (x, y) : (%d, %d) \n", j - 1, i);
							still_empty -= 1;
						}
					}
				}
			}
		}
	}

	return still_empty;
}

// check_jump => x[0] & x[2] are "X", which means in rule two, x[1] must be "O"
int check_jump(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty) {
	for(int i = 0; i < N; i++) { 
		// check x_row
		if(*(x_num_row + i) >= 2) {
			for(int j = 0; j < nCols - 2; j++) {
				if((*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 2)) && (*(int_puzzle_arr + i * nCols + j) == 1)) {
					if (*(int_puzzle_arr + i * nCols + j + 1) != 2) {
						*(int_puzzle_arr + i * nCols + j + 1) = 2;
						printf("Now for row jump assigned 'O' (x, y) : (%d, %d) \n", i, j + 1);
						still_empty -= 1;
					}
				}
			}
		}

		// check o_row
		if(*(o_num_row + i) >= 2) {
			for(int j = 0; j < nCols - 2; j++) {
				if((*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 2)) && (*(int_puzzle_arr + i * nCols + j) == 2)) {
					if (*(int_puzzle_arr + i * nCols + j + 1) != 1) {
						*(int_puzzle_arr + i * nCols + j + 1) = 1;
						printf("Now for row jump assigned 'X' (x, y) : (%d, %d) \n", i, j + 1);
						still_empty -= 1;
					}
				}
			}
		}

		// check x_col
		if(*(x_num_col + i) >= 2) {
			for(int j = 0; j < nCols - 2; j++) {
				if((*(int_puzzle_arr + j * nCols + i) == *(int_puzzle_arr + (j + 2) * nCols + i)) && (*(int_puzzle_arr + j * nCols + i) == 1)) {
					if (*(int_puzzle_arr + (j + 1) * nRows + i) != 2) {
						*(int_puzzle_arr + (j + 1) * nRows + i) = 2;
						printf("Now for col jump assigned 'O' (x, y) : (%d, %d) \n", j + 1, i);
						still_empty -= 1;
					}
				}
			}
		}

		// check o_col
		if(*(o_num_col + i) >= 2) {
			for(int j = 0; j < nCols - 2; j++) {
				if((*(int_puzzle_arr + j * nCols + i) == *(int_puzzle_arr + (j + 2) * nCols + i)) && (*(int_puzzle_arr + j * nCols + i) == 2)) {
					if (*(int_puzzle_arr + (j + 1) * nRows + i) != 1) {
						*(int_puzzle_arr + (j + 1) * nRows + i) = 1; 
						printf("Now for col jump assigned 'X' (x, y) : (%d, %d) \n", j + 1, i);
						still_empty -= 1;
					}
				}
			}
		}
	}

	return still_empty;
}


/* rule 1, "X" & "O" have same numers in each row and each column */
// rule 1
int check_sameNum_XO(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty) {
	for(int i = 0; i < N; i++) {

		// check for Rows
		// 1st only one empty space left
		if((*(x_num_row + i) + *(o_num_row + i)) == nRows - 1) {
			for(int j = 0; j < nCols; j++) {
				if(*(x_num_row + i) > *(o_num_row + i)) {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 2;
						printf("Now for row sameNum assigned 'O' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				} else {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 1;
						printf("Now for row sameNum assigned 'X' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
		}

		// 2nd two empty space left
		if((*(x_num_row + i) + *(o_num_row + i)) == nRows - 2) {
			if(*(x_num_row + i) > *(o_num_row + i)) {
				for(int j = 0; j < nCols; j++) {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 2;
						printf("Now for row sameNum assigned 'O' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
			if(*(x_num_row + i) < *(o_num_row + i)) {
				for(int j = 0; j < nCols; j++) {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 1;
						printf("Now for row sameNum assigned 'X' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
		}

		// check for Columns
		// 1st only one empty space left
		if((*(x_num_col + i) + *(o_num_col + i)) == nCols - 1) {
			for(int j = 0; j < nRows; j++) {
				if(*(x_num_col + i) > *(o_num_col + i)) {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 2;
						printf("Now for col sameNum assigned 'O' (x, y) : (%d, %d) \n", j, i);
						still_empty -= 1;
					}
				} else {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 1;
						printf("Now for col sameNum assigned 'X' (x, y) : (%d, %d) \n", j, i);
						still_empty -= 1;
					}
				}
			}
		}

		// 2nd two empty space left
		if((*(x_num_col + i) + *(o_num_col + i)) == nRows - 2) {
			if(*(x_num_col + i) > *(o_num_col + i)) {
				for(int j = 0; j < nCols; j++) {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 2;
						printf("Now for row sameNum assigned 'O' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
			if(*(x_num_col + i) < *(o_num_col + i)) {
				for(int j = 0; j < nCols; j++) {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 1;
						printf("Now for row sameNum assigned 'X' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
		}

		// each of the row or column has "X" or "O" meet the limit
		if((*(x_num_row + i) == nRows / 2) || (*(o_num_row + i) == nRows / 2)) {
			for(int j = 0; j < nCols; j++) {
				if(*(x_num_row + i) > *(o_num_row + i)) {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 2;
						printf("Now for row sameNum assigned 'O' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				} else {
					if(*(int_puzzle_arr + i * nCols + j) == 0) {
						*(int_puzzle_arr + i * nCols + j) = 1;
						printf("Now for row sameNum assigned 'X' (x, y) : (%d, %d) \n", i, j);
						still_empty -= 1;
					}
				}
			}
		}

		if((*(x_num_col + i) == nCols / 2) || (*(o_num_col + i) == nCols / 2)) {
			for(int j = 0; j < nRows; j++) {
				if(*(x_num_col + i) > *(o_num_col + i)) {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 2;
						printf("Now for col sameNum assigned 'O' (x, y) : (%d, %d) \n", j, i);
						still_empty -= 1;
					}
				} else {
					if(*(int_puzzle_arr + j * nCols + i) == 0) {
						*(int_puzzle_arr + j * nCols + i) = 1;
						printf("Now for col sameNum assigned 'X' (x, y) : (%d, %d) \n", j, i);
						still_empty -= 1;
					}
				}
			}
		}
	}

	return still_empty;
}

// check for rule 1
int check_row_col_valid(int *int_puzzle_arr, int nRows, int nCols, int i, int j) {
	// row[0] for "X", row[1] for "O"
	int row_X = 0;
	int row_O = 0;
	// col[0] for "X", col[1] for "O"
	int col_X = 0;
	int col_O = 0;

	// check for row
	for(int k = 0; k < nRows; k++) {
		if(*(int_puzzle_arr + i * nCols + k) == 1) {
			row_X += 1;
		} else if(*(int_puzzle_arr + i * nCols + k) == 2) {
			row_O += 1;
		}
	}

	// check for col
	for(int k = 0; k < nRows; k++) {
		if(*(int_puzzle_arr + k * nCols + j) == 1) {
			col_X += 1;
		} else if(*(int_puzzle_arr + k * nCols + j) == 2) {
			col_O += 1;
		}
	}

	if(row_X > nRows / 2) { // means "X" exceed the limit, return 1
		return 1;
	}

	if(col_X > nCols / 2) { // means "X" exceed the limit
		return 1;
	}

	if(row_O > nRows / 2) { // means "O" exceed the limit, return 1
		return 1;
	}

	if(col_O > nCols / 2) { // means "O" exceed the limit
		return 1;
	}

	// if all not reach to the limit
	return 0;
}

// for rule 2, used to check when we execute the assign_random function
int check_rule_1and2(int *int_puzzle_arr, int nRows, int nCols) {
	// check for rule 2
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols - 2; j++) {
			// check row valid
			if(*(int_puzzle_arr + i * nCols + j) != 0) {
				if((*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 1)) && (*(int_puzzle_arr + i * nCols + j) == *(int_puzzle_arr + i * nCols + j + 2))) {
					// printf("Invalid puzzle, violate rule 2 !! In (%d, %d) \n", i, j);
					return 0;
				}
			}	

			// check col valid
			if(*(int_puzzle_arr + j * nCols + i) != 0) {
				if((*(int_puzzle_arr + j * nCols + i) == *(int_puzzle_arr + (j + 1) * nCols + i)) && (*(int_puzzle_arr + j * nCols + i) == *(int_puzzle_arr + (j + 2) * nCols + i))) {
					// printf("Invalid puzzle, violate rule 2 !! In (%d, %d) \n", i, j);
					return 0;
				}
			}
		}
	}

	// check for rule 1
	int check_rule1;

	// check row
	for(int i = 0; i < nRows; i++) {
		check_rule1 = check_row_col_valid((int *)int_puzzle_arr, nRows, nCols, i, i);

		// if violate
		if(check_rule1 == 1) {
			return 0;
		}
	}

	return 1;
}

// check for rule 3
int check_rule_3(int *int_puzzle_arr, int nRows, int nCols) {
	int check_arr[nRows * nCols];

	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			*(check_arr + i * nCols + j) = *(int_puzzle_arr + i * nCols + j);
		}
	}

	// check for each row
	for(int i = 0; i < nRows - 1; i++) {
		for(int q = i + 1; q < nRows; q++) {
			int same = 0;

			for(int j = 0; j < nCols; j++) {
				// check for row
				if (*(check_arr + q * nCols + j) == *(int_puzzle_arr + i * nCols + j)) {
					same += 0; // equals => 0
				} else {
					same += 1; // not equal => 1
					break;
				}
			}

			// violate, return 0
			if(same == 0) {
				return 0; 
			}
		}
	}

	// check for each col
	for(int i = 0; i < nRows - 1; i++) {
		for(int q = i + 1; q < nRows; q++) {
			int same = 0;

			for(int j = 0; j < nCols; j++) {
				// check for row
				if(*(check_arr + j * nCols + q) == *(int_puzzle_arr + j * nCols + i)) {
					same += 0; // equals => 0
				} else {
					same += 1; // not equal => 1
					break;
				}
			}

			// violate, return 0
			if(same == 0) {
				return 0; 
			}
		}
	}

	return 1; // not violate, return 1
}

/* some condition that rule 1, 2 are not fit, 
and now we have to assign a random "X" or "O" into the array to give it a try */

int try_assign_random(int start, int z, int *int_puzzle_arr, int nRows, int nCols, int still_empty, int *q_index_row, int *q_index_col) {
	if(start == z) {
		return 0;
	}

	int i = q_index_row[start];
	int j = q_index_col[start];

	// always try to assign "X" first, which is represented by 1
	for(int s = 1; s < 3; s++) {
		*(int_puzzle_arr + i * nCols + j) = s;
		if(s == 1){
			printf("Try to assign 'X' in (%d, %d).\n", i, j);
		} else {
			printf("Try to assign 'O' in (%d, %d).\n", i, j);
		}

		// check valid or not
		// if assign "X" violate, then restore to original puzzle_arr and continue to try "O"
		if((check_rule_1and2((int *)int_puzzle_arr, nRows, nCols) == 0) || (check_rule_3((int *)int_puzzle_arr, nRows, nCols)) == 0) {
			*(int_puzzle_arr + i * nCols + j) = 0;
			continue;
		} else {
			if(try_assign_random((start + 1), z, (int *)int_puzzle_arr, nRows, nCols, still_empty, (int *)q_index_row, (int *)q_index_col) == 0) {
				return 0;
			} else {
				*(int_puzzle_arr + i * nCols + j) = 0;
				continue;
			}
		}
	}

	return 1;
}




















