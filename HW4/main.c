#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <limits.h>
 
#include "tictactoe.h"

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

#define USAGE_STRING "USAGE:./executableName input_file"



int main(int argc, char** argv) {
	int N; // N X N array

	if(argc != 2) {
		fprintf(stderr, "%s\nYou must pass your data file "
			"(in that order) as an argument to this program.\n", USAGE_STRING);
		return 1;
	}

	// read in the file
	FILE *infile = fopen(argv[1],"r");
	if(infile == NULL) {
		fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
		perror("Failed to open file");
		return 2;
	}

	int readIn = fscanf(infile, " %d", &N);

	if(readIn != 1) {
		fprintf(stderr, READ_ERROR_STRING);
		fclose(infile);
		return 1;
	}

	int nRows = N, nCols = N;

	char puzzle_arr[nRows * nCols];

	for(int i = 0; i < nRows; ++i) {
		for(int j = 0; j < nCols; ++j) {
			readIn = fscanf(infile, " %c", &(puzzle_arr[i*nCols+j]));
			if(!readIn) {
				fprintf(stderr, READ_ERROR_STRING );
				return 1;
			}
		}
	}

	// finish assigning the data from the input file into our puzzle array
	fclose(infile);

	// Now the puzzle_arr contains "X" "O" & "?"

	// check if we read the file and assigned the data successfully 
	printf("   Initial puzzle graph : \n");
	printf("  This is a %d X %d puzzle. \n", nRows, nCols);
	printf(" ===========================\n");
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			printf(" %c", puzzle_arr[i*nCols+j]);
		}
		printf("\n");
	}
	printf(" ===========================\n");

	// convert X, O into 1, 2 because comparing char are too complicated
	int int_puzzle_arr[nRows * nCols];
	char x[1] = {"X"};
	char o[1] = {"O"};

	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			if (strncmp((puzzle_arr + i * nCols + j), x, 1) == 0) {
				int_puzzle_arr[i * nCols + j] = 1;
			} else if (strncmp((puzzle_arr + i * nCols + j), o, 1) == 0) {
				int_puzzle_arr[i * nCols + j] = 2;
			} else {
				int_puzzle_arr[i * nCols + j] = 0;
			}
		}
	}

	printf("   Modified puzzle graph : \n");
	printf(" =========================== \n");
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			printf(" %d", int_puzzle_arr[i * nCols + j]);
		}
		printf("\n");
	}
	printf(" =========================== \n");

	int x_num_row[N];
	int o_num_row[N];
	int x_num_col[N];
	int o_num_col[N];
	int still_empty = N * N;

	// printf("%d", still_empty);

	// get the numer of "?"
	still_empty = get_xo_num_row((int *)int_puzzle_arr, nRows, nCols, (int *)x_num_row, (int *)o_num_row, still_empty);
	get_xo_num_col((int *)int_puzzle_arr, nRows, nCols, (int *)x_num_col, (int *)o_num_col);

	printf("  Initial 'X' in each row : \n");
	printf(" ==========================\n");
	for(int i = 0; i < nRows; i++) {
		printf("%d ", x_num_row[i]);
	}
	printf("\n ==========================\n");

	printf("  Initial 'O' in each row : \n");
	printf(" ==========================\n");
	for(int i = 0; i < nRows; i++) {
		printf("%d ", o_num_row[i]);
	}
	printf("\n ==========================\n");

	printf("  Initial 'X' in each col : \n");
	printf(" ==========================\n");
	for(int i = 0; i < nCols; i++) {
		printf("%d ", x_num_col[i]);
	}
	printf("\n ==========================\n");

	printf("  Initial 'O' in each col : \n");
	printf(" ==========================\n");
	for(int i = 0; i < nCols; i++) {
		printf("%d ", o_num_col[i]);
	}
	printf("\n ==========================\n");

	printf("There is still %d empty space.\n", still_empty);

	// testing
	printf("N / 2 = %d \n", (N/2));

	// record old data
	int old_still_empty = N * N;
	int check_change = 0;
	// int old_puzzle_arr[nRows * nCols];
	int record_still_empty = N * N;
	int record_puzzle_arr[nRows * nCols];

	int try_assign = 0;

	int z;

	// initialize passed_pt to avoid any segmentation fault
	// for(int i = 0; i < nRows; i++) {
	// 	for(int j = 0; j < nCols; j++) {
	// 		passed_pt[i * nCols + j] = 0;
	// 	}
	// }


	while(still_empty > 0) {
	// for(int a = 0; a < 10; a++) {
		still_empty = N * N;

		still_empty = get_xo_num_row((int *)int_puzzle_arr, nRows, nCols, (int *)x_num_row, (int *)o_num_row, still_empty);
		get_xo_num_col((int *)int_puzzle_arr, nRows, nCols, (int *)x_num_col, (int *)o_num_col);
		
		// check consecutive
		still_empty = check_consecutive((int *)int_puzzle_arr, N, nRows, nCols, (int *)x_num_row, (int *)o_num_row, (int *)x_num_col, (int *)o_num_col, still_empty);
		
		// check jump
		still_empty = check_jump((int *)int_puzzle_arr, N, nRows, nCols, (int *)x_num_row, (int *)o_num_row, (int *)x_num_col, (int *)o_num_col, still_empty);
		
		// check same numer of "X" "O"
		still_empty = check_sameNum_XO((int *)int_puzzle_arr, N, nRows, nCols, (int *)x_num_row, (int *)o_num_row, (int *)x_num_col, (int *)o_num_col, still_empty);

		printf("   Modified puzzle graph : \n");
		printf(" =========================== \n");
		for(int i = 0; i < nRows; i++) {
			for(int j = 0; j < nCols; j++) {
				printf(" %d", int_puzzle_arr[i * nCols + j]);
			}
			printf("\n");
		}
		printf(" =========================== \n");

		printf("There is still %d empty space. \n", still_empty);

		if((old_still_empty == still_empty) && (still_empty != 0)) {

			// z = still_empty, means we have to try assign at most z times
			z = still_empty;
			printf("z = %d \n", z);

			// recording the empty space index
			int q_index_row[still_empty];
			int q_index_col[still_empty];

			// try assign "X" "O" 
			get_Q_index((int *)int_puzzle_arr, nRows, nCols, (int *)q_index_row, (int *)q_index_col, still_empty);

			printf(" =========================== \n");
			for(int a = 0; a < still_empty; a++) {
				printf(" %d ", q_index_row[a]);
				printf(" %d ", q_index_col[a]);
				printf("\n");
			}
			printf(" =========================== \n");

			// here we assign start = 0.  start
			still_empty = try_assign_random(0, z, (int *)int_puzzle_arr, nRows, nCols, still_empty, (int *)q_index_row, (int *)q_index_col);
			
			// printf("    check passed points : \n");
			// printf(" =========================== \n");
			// for(int i = 0; i < nRows; i++) {
			// 	for(int j = 0; j < nCols; j++) {
			// 		printf(" %d", passed_pt[i * nCols + j]);
			// 	}
			// 	printf("\n");
			// }
			// printf(" =========================== \n");

			if(still_empty == 0) {
				break;
			}
		}
		old_still_empty = still_empty;
	}

	// print the final puzzle graph in int
	printf("   Modified puzzle graph : \n");
	printf(" =========================== \n");
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			printf(" %d", int_puzzle_arr[i * nCols + j]);
		}
		printf("\n");
	}
	printf(" =========================== \n");

	printf("There is still %d empty space. \n", still_empty);


	// check if we can assign char directly into the array
	// puzzle_arr[0] = o[0];
	// printf(" ===========================\n");
	// for(int i = 0; i < nRows; i++) {
	// 	for(int j = 0; j < nCols; j++) {
	// 		printf(" %c", puzzle_arr[i*nCols+j]);
	// 	}
	// 	printf("\n");
	// }
	// printf(" ===========================\n");
	// Well, we have to store the char "X" "O" in the array x and o for the transformation

	// test for array usage
	// printf("int_puzzle_arr[i * nCols + j] for (i,j) = (0,0) will be %d \n", int_puzzle_arr[0]);


	// transform the int_puzzle_arr back to char puzzle_arr
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			if (int_puzzle_arr[i * nCols + j] == 1) {
				puzzle_arr[i * nCols + j] = x[0];
			} else {
				puzzle_arr[i * nCols + j] = o[0];
			}
		}
	}

	// double check for rule three
	if(check_rule_3((int *)int_puzzle_arr, nRows, nCols) == 0) {
		printf("Please don't! I wanna sleep QAQ \n");
	} else {
		printf("Congratulation!! Well done ~ \n");
	}


	printf("     Final puzzle graph : \n");
	printf(" ===========================\n");
	for(int i = 0; i < nRows; i++) {
		for(int j = 0; j < nCols; j++) {
			printf(" %c", puzzle_arr[i * nCols + j]);
		}
		printf("\n");
	}
	printf(" ===========================\n");
}


