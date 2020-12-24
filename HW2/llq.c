#include <stdio.h>
#include <stdlib.h>

#include "llq.h"

// Create an empty queue 
LLQueue *LLQ_create() {
    LLQueue *LLQ = (LLQueue*)malloc(sizeof(LLQueue));
    
    /* Sometimes the initial LLQ might have some garbage value inside, 
    and will cause the memory error (segmentation fault, so we need to 
    initialize the LLQ->head and LLQ->tail*/
    LLQ->head = NULL; 
    LLQ->tail = NULL;

    if (LLQ == NULL) {
        return NULL;
    }
    return LLQ;
};

// Insert a Node into our LLQueue
int LLQ_insert(LLQueue *LLQ, double data) {
    QNode *temp = (QNode*)malloc(sizeof(QNode));

    if (temp == NULL) {
        return -1;
    }

    temp->key = data;
    temp->next = NULL;

    if(LLQ->head == NULL) {
        LLQ->head = temp;
        LLQ->tail = temp;
        // printf("LLQ->head is %f.\n", LLQ->head->key);
        // printf("LLQ->tail is %f.\n", LLQ->tail->key);
        return 0;
    }

    LLQ->tail->next = temp;
    LLQ->tail = temp;
    // printf("LLQ->head is %f.\n", LLQ->head->key);
    // printf("LLQ->tail is %f.\n", LLQ->tail->key);
    return 0;
};

// // Delete a Node from the queue LLQ, returns the data item or 0 if the queue is empty
double LLQ_delete(LLQueue *LLQ) {
    if (LLQ->head != NULL) {
        QNode *rmNode = LLQ->head;
        double rmKey = rmNode->key;
        LLQ->head = LLQ->head->next;
        free(rmNode);
        return rmKey;
    }
    return 0;
};

/* Search for the value data within the queue, which return a pointer to the data 
item or NULL if the data item is not present */
double *LLQ_Search(LLQueue *LLQ, double data) {
    QNode *searchPoint = LLQ->head;

    while ((searchPoint != NULL) && (searchPoint->key != data)) {
        searchPoint = searchPoint->next;
    }

    if (searchPoint != NULL) {
        return &(searchPoint->key);
    } else {
        return NULL;
    }
};

// Return the minimum of the items in the queue
double LLQ_minimum(LLQueue *LLQ) {
    QNode *currPoint = LLQ->head;

    if (currPoint == NULL) {
        return 0; // 0 means no data inside the queue
    }
    double findMin = currPoint->key;

    while (currPoint != NULL) {
        if (currPoint->key < findMin) {
            findMin = currPoint->key;
        }
        currPoint = currPoint->next;
    }
    return findMin;
};

// Return the maximum of the items in the queue
double LLQ_maximum(LLQueue *LLQ) {
    QNode *currPoint = LLQ->head;
    
    if (currPoint == NULL) {
        return 0; // 0 means no data inside the queue
    }
    double findMax = currPoint->key;
    
    while (currPoint != NULL) {
        if (currPoint->key > findMax) {
            findMax = currPoint->key;
        }
        currPoint = currPoint->next;
    }
    return findMax;
};

// return the number of items currently in the queue
unsigned int LLQ_count(LLQueue *LLQ) {
    QNode *currPoint = LLQ->head;
    int count = 0;
    
    while (currPoint != NULL) {
        count++;
        currPoint = currPoint->next;
    }
    return count;
};


// print items in the queue
void LLQ_print(LLQueue *LLQ) {
    QNode *currPrint = LLQ->head;

    if (currPrint == NULL) {
        printf("\nThis queue now is empty!!!\n"); // empty queue
    }

    while(currPrint != NULL) {
        printf("%.3f ", currPrint->key);
        currPrint = currPrint->next;
    }
};

// free everything
void LLQ_free(LLQueue *LLQ) {
    QNode *temp;

    while(LLQ->head != NULL) {
        temp = LLQ->head;
        LLQ->head = LLQ->head->next;
        free(temp);
    }

    free(LLQ);
};