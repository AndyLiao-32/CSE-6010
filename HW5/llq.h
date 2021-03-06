#ifndef MY_LLQ_H
#define MY_LLQ_H

// Define Node in Queue
typedef struct QNode {
    int key;
    int pred;
    struct QNode *next;
} QNode; 

// Define Linked list Queue
typedef struct LLQueue {
    QNode *head;
    QNode *tail;
} LLQueue;

// Create an empty queue 
LLQueue *LLQ_create();

// Insert a Node into our LLQueue
int LLQ_insert(LLQueue *LLQ, int data, int pred);

// Delete a Node from the queue LLQ, returns the data item or 0 if the queue is empty
int LLQ_delete(LLQueue *LLQ);

/* Search for the value data within the queue, which return a pointer to the data 
item or NULL if the data item is not present */
int LLQ_Search(LLQueue *LLQ, int data);

// // Return the minimum of the items in the queue
// double LLQ_minimum(LLQueue *LLQ);

// // Return the maximum of the items in the queue
// double LLQ_maximum(LLQueue *LLQ);

// // return the number of items currently in the queue
unsigned int LLQ_count(LLQueue *LLQ);

// print items in the queue
void LLQ_print(LLQueue *LLQ);

// just for check
void LLQ_print_pred(LLQueue *LLQ);

// free everything
void LLQ_free (LLQueue *LLQ);

#endif