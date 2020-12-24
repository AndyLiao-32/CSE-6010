#ifndef MY_PUZZLE_H
#define MY_PUZZLE_H

// int *x_num_row, int *o_num_row are two arrays which stored the number of "X" & "O" for each row
int get_xo_num_row(int *int_puzzle_arr, int nRows, int nCols, int *x_num_row, int *o_num_row, int still_empty);
void get_xo_num_col(int *int_puzzle_arr, int nRows, int nCols, int *x_num_col, int *o_num_col);

// get the index for all "?"
void get_Q_index(int *int_puzzle_arr, int nRows, int nCols, int *q_index_row, int *q_index_col, int still_empty);

// for rule 2
int check_consecutive(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty);
int check_jump(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty);

// for rule 1
int check_sameNum_XO(int *int_puzzle_arr, int N, int nRows, int nCols, int *x_num_row, int *o_num_row, int *x_num_col, int *o_num_col, int still_empty);

// check for rule 1
int check_row_col_valid(int *int_puzzle_arr, int nRows, int nCols, int i, int j);

// check for rule 2
int check_rule_1and2(int *int_puzzle_arr, int nRows, int nCols);

// check for rule 3
int check_rule_3(int *int_puzzle_arr, int nRows, int nCols);

// assign random, use the recursion method
int try_assign_random(int start, int z, int *int_puzzle_arr, int nRows, int nCols, int still_empty, int *q_index_row, int *q_index_col);


#endif