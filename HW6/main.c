#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include "network.h"
#include "model.h"

#define numAgents 500
#define numIterations 100
#define numNearestNeighbors 10
#define pInfection 0.05
#define pRecovery 0.1
#define pReplaceRandom 0.25
#define pDisconnect 0.5

int main()
{
    int size = numAgents;
    int array[size];

    srand (time(NULL));

    // create the network array
    create_array(size, array);
    
    int neighbor = numNearestNeighbors;
    int Bdj[size*size];
    for (int i = 0; i < size; i++)
    { 
        for (int j = 0; j < size; j++)
        { 
            Bdj[i*size + j] = 0;
        }
    }

    // create the adjacency matrix randomly
    create_AdjMatrix_random(neighbor, size, array, Bdj);

    int state[size];
    int state_change[size];
    for (int i = 0; i < size; i++)
    {
        state[i] = 0;
    }
    state[array[0]] = 1;

    // update
    update_state(size, state_change, state);
    
    // iteration
    iteration(size, array, Bdj, state, state_change);
    
}



