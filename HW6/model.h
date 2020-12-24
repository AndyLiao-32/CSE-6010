#ifndef MY_MODEL_H
#define MY_MODEL_H

// assign temporary array state_change[] to state[] for updating the state of agents.
void update_state(int size, int* state, int* state_change);

// print the matrix
void print_matrix(int size, int* Bdj);

// print the state
void print_state(int size, int* state);

// Calculate the number of infected, recovered and susceptible agents in each iteration.
int calculate(int size, int* state);

// Calculate the sum of infected and recovered agents in each iteration.
int calculate1(int size, int* state);

// iteration
void iteration(int size, int* array, int* Bdj, int* state, int* state_change);

#endif