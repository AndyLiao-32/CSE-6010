#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include "network.h"

#define numAgents 500
#define numIterations 100
#define numNearestNeighbors 10
#define pInfection 0.05
#define pRecovery 0.1
#define pReplaceRandom 0.25
#define pDisconnect 0.5

void create_array(int size, int* array)            // Create an array which represents the neighbor relationship with each agent.
{
    for (int i = 0; i < size; i++)
    {   
        *(array + i) = i;
    }
    
    // Randomly change the order of agents in array.
    for (int i = 0; i < size; i++)
    {
        int temp = array[i];
        int randomIndex = rand() % size;
        *(array + i) = *(array + randomIndex);
        *(array + randomIndex) = temp;
    }
}

void create_AdjMatrix_random(int neighbor, int size, int* array, int* Adj)   // Add pReplaceRandom in create_AdjMatrix() to make edges have
{                                                                                        // specified probability to randomly pick other agents rather
    if (neighbor % 2 == 1)                                                               // than original neighbor network.
    {
        neighbor += 1;
        printf("Warning! numNeighbors is odd, have increased 1\n");
    }

    if (neighbor > size)
    {
        if (size % 2 == 1)
        {
            neighbor = size-1;
        }
        
        else
        {
            neighbor = size;
        }
        printf("Warning! numNeighbors is larger than size, have adjusted to size\n");
    }

    double pReplaceRandom1 = pReplaceRandom;
    if (pReplaceRandom > 1)
    {
        pReplaceRandom1 = 1;
        printf("Warning! pReplaceRandom is larger than 1, have adjusted to 1\n");
    }
    else if (pReplaceRandom < 0)
    {
        pReplaceRandom1 = 0;
        printf("Warning! pReplaceRandom is smaller than 0, have adjusted to 0\n");
    }
                                                         
    for (int i = 0; i < size; i++)
    {
        int x = *(array + i);
        for (int j = 1; j <= neighbor/2; j++)
        {
            int random_pick = rand() % (int)(ceil(1/pReplaceRandom1));
            if (random_pick == 0 && pReplaceRandom1 != 0)                   // Randomly choose other agents to connect under the probability pReplaceRandom.
            {
                int random_index = rand() % size;
                *(Adj + x*size + random_index) = 1;
                *(Adj + random_index*size + x) = 1;
            }
            
            else                                                            // Use the original neighbor relationship to connect each other if pReplaceRandom
            {                                                               // does not happen.
                if (i+j > size - 1)
                {
                    int y = *(array + (i + j)%size);
                    *(Adj + x*size + y) = 1;
                    *(Adj + y*size + x) = 1;
                }
                else
                {
                    int y = *(array + i + j);
                    *(Adj + x*size + y) = 1;
                    *(Adj + y*size + x) = 1;
                }
            }
        } 
    }
}