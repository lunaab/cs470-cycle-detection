#include <stdlib.h>
#include "intlist.h"

void initlist(struct intlist* l) {
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
}

int append(struct intlist* l, int value) {
    struct node* new;
    new = (struct node*)malloc(sizeof(struct node));
    if (new == NULL) {
        return -1;
    }
    
    new->value = value;
    new->next = NULL;

    if (l->tail != NULL) {
        l->tail->next = new;
    }

    l->tail = new;

    if (l->head == NULL) {
        l->head = l->tail;
    }

    l->length = l->length + 1;

    return 0;
}

int isempty(struct intlist* l) {
    return l->length == 0;
}
