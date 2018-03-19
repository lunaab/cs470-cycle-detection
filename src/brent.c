/* Brent's Cycle Detection Algorithm */
/* Acquired at: https://www.geeksforgeeks.org/brents-cycle-detection-algorithm/ */

#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"

struct node* brentCycleDetection(struct intlist* list) {
    if (list->head == NULL) {
        return NULL;
    }

    struct node* first_p = list->head;
    struct node* second_p = list->head->next;
    int power = 1;
    int length = 1;

    while (second_p != NULL && second_p != first_p) {

        if (length == power) {
            power *= 2;
            length = 0;
            first_p = second_p;
        }
        
        second_p = second_p->next;
        ++length;
    }

    if (second_p == NULL) {
        return NULL;
    }

    first_p = second_p = list->head;
    while (length > 0) {
        second_p = second_p->next;
        --length;
    }

    while (second_p != first_p) {
        second_p = second_p->next;
        first_p = first_p->next;
    }

    return first_p;
}
