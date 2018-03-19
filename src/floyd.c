/* Floyd's Cycle Detection Algorithm */
/* Acquired at: https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/ */

#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"

int floydCycleDetection(struct intlist* list) {
    struct node* slow_p = list->head;
    struct node* fast_p = list->head;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p)
        {
            printf("Found Loop");
            return 1;
        }
    }
    return 0;
}
