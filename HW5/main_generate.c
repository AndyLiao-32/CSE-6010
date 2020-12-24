#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

// Reference from HW3 helper code
#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

#define USAGE_STRING "USAGE:./executableName write_file_name nRows nCols"

#define random(a,b) ((rand()%(b-a))+a) // result will contain a but not b

int dfs(int selected_i, int selected_j, int nRows, int nCols, int *maze, FILE *fptr) {
	// set the new start point as visited
	*(maze + selected_i*nCols + selected_j) = 1;

	/* use the variable "repeat" to check whether the four direction all have been 
	visited and that means we have to backtrack to the previous node*/
	int repeat = 0,
		count = 0;
	int check_arr[4];

	for (int i = 0; i < 4; i++) {
		check_arr[i] = 0; // index represent -> 0: right, 1: left, 2: down; 3: up
	}

	while (repeat < 4) {
		int dirNum = random(0, 4); // 0: right, 1: left, 2: down; 3: up
		// printf("dirNum : %d \n", dirNum);
		
		// right
		if (dirNum == 0) {
			if ((*(maze + selected_i*nCols + selected_j+1) == 0) && (((selected_i*nCols + selected_j+1)%nCols) != 0)) {
				// printf("The parent and the child : %d  %d \n", (selected_i*nCols + selected_j), (selected_i*nCols + selected_j+1));
				fprintf(fptr, "%d %d \n", (selected_i*nCols + selected_j), (selected_i*nCols + selected_j+1));
				dfs((int) selected_i, (int) selected_j+1, (int) nRows, (int) nCols, (int *) maze, (FILE *) fptr);
			} else { // means this point has been visited
				if (check_arr[0] != 1) { // if we have checked this point before, ignore it
					repeat += 1;
					check_arr[0] = 1;
				}
			}
		}

		// left
		if (dirNum == 1) {
			if ((*(maze + selected_i*nCols + selected_j-1) == 0) && (((selected_i*nCols + selected_j)%nCols) != 0)) {
				// printf("The parent and the child : %d  %d \n", (selected_i*nCols + selected_j), (selected_i*nCols + selected_j-1));
				fprintf(fptr, "%d %d \n", (selected_i*nCols + selected_j), (selected_i*nCols + selected_j-1));
				dfs((int) selected_i, (int) selected_j-1, (int) nRows, (int) nCols, (int *) maze, (FILE *) fptr);
			} else { // means this point has been visited
				if (check_arr[1] != 1) { // if we have checked this point before, ignore it
					repeat += 1;
					check_arr[1] = 1;
				}
			}
		}

		// down
		if (dirNum == 2) {
			if ((*(maze + (selected_i+1)*nCols + selected_j) == 0) && ((((selected_i+1)*nCols + selected_j)) < nRows*nCols)) {
				// printf("The parent and the child : %d  %d \n", (selected_i*nCols + selected_j), ((selected_i+1)*nCols + selected_j));
				fprintf(fptr, "%d %d \n", (selected_i*nCols + selected_j), ((selected_i+1)*nCols + selected_j));
				dfs((int) selected_i+1, (int) selected_j, (int) nRows, (int) nCols, (int *) maze, (FILE *) fptr);
			} else { // means this point has been visited
				if (check_arr[2] != 1) { // if we have checked this point before, ignore it
					repeat += 1;
					check_arr[2] = 1;
				}
			}
		}

		// up
		if (dirNum == 3) {
			if ((*(maze + (selected_i-1)*nCols + selected_j) == 0) && ((((selected_i-1)*nCols + selected_j)) > 0)) {
				// printf("The parent and the child : %d  %d \n", (selected_i*nCols + selected_j), ((selected_i-1)*nCols + selected_j));
				fprintf(fptr, "%d %d \n", (selected_i*nCols + selected_j), ((selected_i-1)*nCols + selected_j));
				dfs((int) selected_i-1, (int) selected_j, (int) nRows, (int) nCols, (int *) maze, (FILE *) fptr);
			} else { // means this point has been visited
				if (check_arr[3] != 1) { // if we have checked this point before, ignore it
					repeat += 1;
					check_arr[3] = 1;
				}
			}
		}

		count++;
	}

	return 0; // means that we need to backtrack to previous point
}

int main(int argc, char** argv) {
	// Input from the command line is referenced from HW3 helper code
	if(argc != 4){
		fprintf(stderr, "%s\nYou must pass your data file, nRows andd nCols"
		"(in that order)as an argument to this program.\n", USAGE_STRING);
		return 1;
	}

	// This section will safely parse the value of k passed in to the program.
	// If the argument cannot be parsed to an integer, or if it is larger than
	// INT_MAX, we error out.
	char *endptr = NULL;
	int base = 10;
	errno = 0;
	long int long_r = strtol(argv[2], &endptr, base);

	// This will trigger if an error was encountered when trying to parse the
	// input, or if the input was not a proper integer (e.g. 124A). This
	// can also trigger if the input is too long to fit even in a long int.
	if((errno != 0) || (*endptr != '\0')) {
		fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
		" \n", argv[2]);
		return 1;
	}
	if((long_r > INT_MAX) || (long_r <= 0)) {
		fprintf(stderr, "The k-value input was:\t%ld\n"
		"nRows must be larger than zero, and no larger than %u.\n", long_r,
		INT_MAX);
		return 1;
	}

	long int long_c = strtol(argv[3], &endptr, base);

	if((errno != 0) || (*endptr != '\0')) {
		fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
		" \n", argv[3]);
		return 1;
	}
	if((long_c > INT_MAX) || (long_c <= 0)) {
		fprintf(stderr, "The k-value input was:\t%ld\n"
		"nCols must be larger than zero, and no larger than %u.\n", long_c,
		INT_MAX);
		return 1;
	}
	

	// Create or open the file to store the maze adjacency list
	// ================================================================================
	// File 1
	FILE *fptr, *fptr2; // fptr2 => for our maze_adjacency list

	fptr = fopen("maze_support_list.txt", "w");

	if(fptr == NULL) {
	    printf("Error!");   
	    exit(1);             
	}

	// First, create a set of random index for i(Rows) and j(Cols)
	int nRows = (int)long_r;
	int nCols = (int)long_c;

	// Write the nRows & nCols to the file
	fprintf(fptr, "%d %d \n", nRows, nCols);
	// fprintf(fptr2, "%d %d \n", nRows, nCols);

	srand((int)time(NULL)); // Create different random number  

	int i = random(0, nRows);
	int j = random(0, nCols);

	int maze[nRows*nCols];

	for (int a = 0; a < nRows; a++) {
		for (int b = 0; b < nCols; b++) {
			maze[a*nCols + b] = 0; // mark as unvisited
		}
	}

	// set the starting point
	maze[i*nCols + j] = 1;

	// set for selected point
	int selected_i = i;
	int selected_j = j;

	// start to build our maze
	dfs((int) selected_i, (int) selected_j, (int) nRows, (int) nCols, (int *) maze, (FILE *) fptr);

	// print the maze
	// printf("\n Final Maze Graph :  \n");
	// for (int a = 0; a < nRows; a++) {
	// 	for (int b = 0; b < nCols; b++) {
	// 		printf(" %d ", maze[a*nCols + b]); // mark as unvisited
	// 	}
	// 	printf("\n");
	// }

	fclose(fptr);
	// ================================================================================

	// store the start and finish point
	fptr = fopen("maze_support_list.txt", "r");

	int start, finish, parent, child;

	if(fptr == NULL) {
	    printf("Error!");   
	    exit(1);             
	}

	int readIn = fscanf(fptr, "%d %d", &nRows, &nCols);

	// Write the start and finish point
	for (int a = 1; a < nRows*nCols; a++) {
		readIn = fscanf(fptr, "%d %d", &parent, &child);
		// for start point
		if (a == 1) {
			start = parent;
		}
		// for finish point
		if (a == nRows*nCols-1) {
			finish = child;
		}
	}

	// check if we get the right start, finish point
	// printf("Start : %d, Finish : %d \n", start, finish);

	fclose(fptr);

	// ================================================================================
	// File 2

	// create an array for sorting the adjacency list
	int maze_adj_list[nRows*nCols*2];

	fptr = fopen("maze_support_list.txt", "r");
	fptr2 = fopen(argv[1], "w");

	if(fptr == NULL) {
	    printf("Error!");   
	    exit(1);             
	}

	if(fptr2 == NULL) {
	    fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
	    perror("Failed to open file");   
	    return 2;             
	}

	int readIn2 = fscanf(fptr, "%d %d", &nRows, &nCols);
	// check the nRows & nCols value
	// printf("nRows & nCols : %d %d \n", nRows, nCols);

	fprintf(fptr2, "%d %d \n", nRows, nCols);
	fprintf(fptr2, "%d %d \n", start, finish);

	maze_adj_list[0] = nRows;
	maze_adj_list[1] = nCols;

	// create the adjacency list file
	for (int a = 1; a < nRows*nCols; a++) {
		int readIn2 = fscanf(fptr, "%d %d", &(maze_adj_list[a*2]), &(maze_adj_list[a*2+1]));
	}

	// check whether we assigned correct or not
	// for (int a = 0; a < nRows*nCols; a++) {	
	// 	printf("%d %d \n", maze_adj_list[a*2], maze_adj_list[a*2+1]);
	// }

	// assign the value to the adjacency list
	for (int a = 0; a < nRows*nCols; a++) {
		for (int b = 1; b < nRows*nCols; b++) {
			// if parent equals to the root
			if (maze_adj_list[b*2] == a) {
				fprintf(fptr2, "%d ", maze_adj_list[b*2+1]);
			} else if (maze_adj_list[b*2+1] == a) { // if child equals to the root
				fprintf(fptr2, "%d ", maze_adj_list[b*2]);
			}
		}
		fprintf(fptr2, "\n");
	}

	// Show successfully generate adjacency list
	printf("Successfully generate adjacency list!! \n");

	fclose(fptr2);
	fclose(fptr);
	// ================================================================================
}


