#include <stdio.h>
#include <stdlib.h>

#include "llq.h"

int main(int argc, char *argv[]) {
    int sw, c, data, init=0;
    double a, del, sr1;
    double *sr2;

    printf("Welcome to our Linked List Queue Menu!!");
    printf("\n======================");
    printf("\n 1 - LLQ_Insert");
    printf("\n 2 - LLQ_Delete");
    printf("\n 3 - LLQ_Search");
    printf("\n 4 - LLQ_Minimum");
    printf("\n 5 - LLQ_Maximum");
    printf("\n 6 - LLQ_Count");
    printf("\n 7 - LLQ_Print");
    printf("\n 8 - LLQ_free");
    printf("\n 9 - Exit");
    printf("\n======================");
    LLQueue *q = LLQ_create();
    LLQ_insert(q, 3.5);
    LLQ_insert(q, 10.6);
    LLQ_insert(q, 22.3);
    LLQ_insert(q, 31.0);
    while(init != 9) {
        printf("\n Select your Choice : ");
        scanf("%d", &sw);
        switch (sw) {
            case 1:
                printf("\nInput: ");
                scanf("%lf", &a);
                data = LLQ_insert(q, a);
                if (data == -1) {
                    printf("\nFail to insert the data, return %d.", data);
                } else {
                    printf("\nSuccessfully insert the data, return %d.", data);
                }
                break;
            case 2:
                del = LLQ_delete(q);
                if (del == 0) {
                    printf("\nReturn %lf. The queue is empty, nothing can be deleted.", del);
                } else {
                    printf("\nSuccessfully delete. The delete item is %.3lf.", del);
                }
                break;
            case 3:
                printf("\nInput the data you want to search : ");
                scanf("%lf", &sr1);
                sr2 = LLQ_Search(q, sr1);
                printf("\nHere's the pointer which you try to search, %p", sr2);
                break;
            case 4:
                printf("\nThe minimum item is %.3f.", LLQ_minimum(q));
                break;
            case 5:
                printf("\nThe maximum item is %.3f.", LLQ_maximum(q));
                break;
            case 6:
                printf("\nThere are %d items currently in the queue.", LLQ_count(q));
                break;
            case 7:
                LLQ_print(q);
                break;
            case 8:
                LLQ_free(q);
                printf("The memory now is free!!");
                break;
            case 9:
                printf("\nDo you sure you want to quit the program? (1 (yes) / 2 (no)) : ");
                scanf("%d", &c);
                if (c == 1) {
                    init = 9;
                    break;
                } else if (c == 2) {
                    break;
                } else {
                    printf("\nMake sure you input a correct number (1 or 2), Thank you!");
                    break;
                }
            default:
                printf("\n404 Not found, please enter a correct choice!!!");
                break;
        }
    }
}