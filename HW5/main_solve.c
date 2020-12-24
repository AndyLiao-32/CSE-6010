#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include "llq.h"

// Reference from HW3 helper code
#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

#define USAGE_STRING "USAGE:./executableName read_file_name"

int main(int argc, char** argv) {
	// Input from the command line is referenced from HW3 helper code
	if(argc != 2) {
		fprintf(stderr, "%s\nYou must pass your data file, nRows andd nCols"
		"(in that order)as an argument to this program.\n", USAGE_STRING);
		return 1;
	}

	// ================================================================================

	// store the start and finish point
	FILE *fptr = fopen(argv[1], "r");

	int start, finish, parent, child;

	if(fptr == NULL) {
	    printf("Error!");   
	    exit(1);             
	}

	int nRows, nCols;
	int readIn = fscanf(fptr, "%d %d", &nRows, &nCols);
	readIn = fscanf(fptr, "%d %d", &start, &finish);

	// check nRows nCols
	// printf("nRows : %d, nCols : %d \n", nRows, nCols);
	// check if we get the right start, finish point
	// printf("Start : %d, Finish : %d \n", start, finish);

	fclose(fptr);

	// ================================================================================

	// Create our parent child list

	int index = 0;
	int data = 0;
	int count_maze = 1;

	fptr = fopen(argv[1], "r");

	if (fptr == NULL) {
	    fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
	    perror("Failed to open file");   
	    return 2;             
	}

	readIn = fscanf(fptr, "%d %d", &nRows, &nCols);
	readIn = fscanf(fptr, "%d %d", &start, &finish);

	int result = nRows*nCols+1; // using this number because we won't have the node which is out of range

	int maze_parent_child[(nRows*nCols)*2];

	maze_parent_child[0] = nRows;
	maze_parent_child[1] = nCols;

	for (int a = 1; a < (nRows*nCols*2-1); a++) {
		readIn = fscanf(fptr, "%d ", &data);

		// check whether the node belongs to the parent
		if ((data != (index + 1)) && (data != (index - 1)) && (data != (index + nCols)) && (data != (index - nCols))) {
			index += 1;
		}

		// check whether the node has been visited
		if (data < index) {
			continue;
		}

		maze_parent_child[count_maze*2] = index;
		maze_parent_child[count_maze*2+1] = data;

		count_maze += 1;
	}

	// check maze_parent_child
	// printf("Check for our maze array : \n");

	// for (int a = 0; a < nRows*nCols; a++) {
	// 	printf("%d %d \n", maze_parent_child[a*2], maze_parent_child[a*2+1]);
	// }

	fclose(fptr);

	// ================================================================================

	// BFS Process

	// solve for the maze, using LLQ
	LLQueue *Q_bfs = LLQ_create(); // implement the bfs function
	LLQueue *Q_result = LLQ_create(); // store the result path

	int begin = start;
	LLQ_insert(Q_result, begin, begin);

	int visited = -1;

	while (result != finish) {
		
		for (int i = 1; i < nRows*nCols; i++) {
			if ((maze_parent_child[i*2] == begin) || (maze_parent_child[i*2+1] == begin)) {
				if (maze_parent_child[i*2] == begin) {

					if (visited == maze_parent_child[i*2+1]) {
						continue;
					}

					LLQ_insert(Q_bfs, maze_parent_child[i*2+1], maze_parent_child[i*2]);
					LLQ_insert(Q_result, maze_parent_child[i*2+1], maze_parent_child[i*2]);
					// printf("Insert into Q_bfs : %d \n", maze_parent_child[i*2+1]);
					// check whether we found the finish point or not
					if (maze_parent_child[i*2+1] == finish) {				
						// count++;
						// printf("Insert into Q_result : %d \n", finish);
						result = finish;
						break;
					}
				} else if (maze_parent_child[i*2+1] == begin) {

					if (visited == maze_parent_child[i*2]) {
						continue;
					}

					LLQ_insert(Q_bfs, maze_parent_child[i*2], maze_parent_child[i*2+1]);
					LLQ_insert(Q_result, maze_parent_child[i*2], maze_parent_child[i*2+1]);
					// printf("Insert into Q_bfs : %d \n", maze_parent_child[i*2]);
					// check whether we found the finish point or not
					if (maze_parent_child[i*2] == finish) {				
						// count++;
						// printf("Insert into Q_result : %d \n", finish);
						result = finish;
						break;
					}
				}
			}
		}
		visited = begin;

		begin = LLQ_delete(Q_bfs);
	}

	// check our queue after BFS
	// printf("BFS check : first is key \n");
	// LLQ_print(Q_result);
	// printf("BFS check : second is pred \n");
	// LLQ_print_pred(Q_result);

	// store the BFS result into an array called BFS_modified
	int count = LLQ_count(Q_result);
	// printf("%d items in the queue \n", count);

	int BFS_modified[count]; // due to that our path will not be larger than the count

	for (int i = 0; i < count; i++) {
		BFS_modified[i] = nRows*nCols + 1;
	}

	int search = 0; // set the default value
	int index2 = 0;

	// search = LLQ_Search(Q_result, finish);
	// printf("pred of finish : %d \n", search);

	int end = finish;

	while (index2 < count) {
		search = LLQ_Search(Q_result, end);
		end = search;

		if (search == -1) {
			break;
		}

		BFS_modified[index2] = search;

		index2++;
	}

	// find the index of the start point
	for (int i = 0; i < count; i++) {
		if (BFS_modified[i] == start) {
			index2 = i;
			// printf("finish index = %d \n", index);
			break;
		}
	}

	// print out the maze solution
	printf("The solution of the maze : \n");	
	for (int i = index2; i >=0; i--) {
		printf("%d ", BFS_modified[i]);
	}
	printf("%d ", finish);
	printf("\n");

	// free the LLQ
	LLQ_free(Q_bfs);
	LLQ_free(Q_result);
}


