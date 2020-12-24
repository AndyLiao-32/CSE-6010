#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#include "model.h"

#define numAgents 500
#define numIterations 100
#define numNearestNeighbors 10
#define pInfection 0.05
#define pRecovery 0.1
#define pReplaceRandom 0.25
#define pDisconnect 0.5

void update_state(int size, int* state, int* state_change)        // assign temporary array state_change[] to state[] for updating the state of agents.
{
    for (int i = 0; i < size; i++)
    {
        *(state + i) = *(state_change + i);
    }
}

void print_matrix(int size, int* Bdj)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", *(Bdj + i*size + j));
        }
        printf("\n");
    }
}

void print_state(int size, int* state)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(state + i));
    }
    printf("\n");
}

int calculate(int size, int* state)          // Calculate the number of infected, recovered and susceptible agents in each iteration.
{
    int infect = 0;
    int susceptible = 0;
    int recovery = 0;
    for (int i = 0; i < size; i++)
    {
        if (*(state + i) == 0)
        {
            susceptible += 1;
        }
        else if (*(state + i) == 1)
        {
            infect += 1;
        }
        else if (*(state + i) == -1)
        {
            recovery += 1;
        }
    }
    printf("Infect: %d, Recovery: %d, Susceptible: %d\n\n", infect, recovery, susceptible);
    return infect;
}

int calculate1(int size, int* state)          // Calculate the sum of infected and recovered agents in each iteration.
{
    int infect_recovery = 0;
    for (int i = 0; i < size; i++)
    {
        if (*(state + i) != 0)
        {
            infect_recovery += 1;
        }
    }
    return infect_recovery;
}

void iteration(int size, int* array, int* Bdj, int* state, int* state_change)
{
    int iter = numIterations;                      // Iterate numIterations times and record the number of states in each iteration.
    int iter1 = 1;
    int num_infect = 0;
    int record = 0;
    while (iter > 0)
    {
        printf("Iteration %d\n", iter1);
        
        int num_infect1 = calculate(size, state);
        if (num_infect1 > num_infect)
        {
            num_infect = num_infect1;
            record = iter1;
        }
        printf("\n");

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(Bdj + i*size + j) == 1 && *(state + j) == 1 && *(state + i) == 0)      // If i and j agents have connection and j is infected, then i has probability of pInfection
                {                                                          // to be infected and the state of i will be changed from 0 (susceptible) to 1 (infected).
                    int infect = rand() % (int)(ceil(1/pInfection));
                    if (infect == 0)
                    {
                        *(state_change + i) = 1;                        // The change in state will be stored in an temporary array because the effect of change will
                    }                                               // only happen in next iteration.
                }
            }

            if (*(state + i) == 1)                                      // If the agents are infected, they have probability of pRecovery to recover from 1 (infected)
            {                                                       // to -1 (recovery).
                int recovery = rand() % (int)(ceil(1/pRecovery));
                if (recovery == 0)
                {
                    *(state_change + i) = -1;
                }
            }
        }

        if (pDisconnect != 0)                                        // If the agent is infected, the edges with other agents have probability of pDisconnect
        {                                                            // to be removed.
            double pDisconnect1 = pDisconnect;
            for (int i = 0; i < size; i++)
            {
                if (*(state + i) == 0 && *(state_change + i) == 1)
                {
                    for (int j = 0; j < size; j++)
                    {
                        int disconnect = rand() % (int)(ceil(1/pDisconnect1));
                        if (*(Bdj + i*size + j) == 1 && disconnect == 0)
                        {
                            *(Bdj + i*size + j) = 0;
                            *(Bdj + j*size + i) = 0;
                        }
                    }     
                }
            }
        }
    
        update_state(size, state, state_change);                     // Update the state for next iteration.
        iter -= 1;
        iter1 += 1;
    }
    printf("The maximum number of infected individuals in a single iteration: %d\n\n", num_infect);
    printf("The iteration number at which the maximum number of infected individuals occurs: %d\n\n", record);
    printf("After %d iteration(s): \n\n", numIterations);
    calculate(size, state);
    printf("The sum of the number of currently infected and recovered individuals after the last iteration: %d\n\n", calculate1(size, state));
}