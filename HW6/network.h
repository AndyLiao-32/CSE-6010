#ifndef MY_NETWORK_H
#define MY_NETWORK_H

// Create an array which represents the neighbor relationship with each agent.
void create_array(int size, int* array); 

/* Add pReplaceRandom in create_AdjMatrix() to make edges have specified 
probability to randomly pick other agents rather than original neighbor network.*/
void create_AdjMatrix_random(int neighbor, int size, int* array, int* Adj);

#endif