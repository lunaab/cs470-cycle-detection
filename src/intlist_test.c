/* Test file for intlist functions */

#include <stdlib.h>
#include "intlist.h"

void test_init(struct intlist* l) {
    initlist(l)
    if (l->head == NULL) {
        printf("Test initlist head == NULL: PASS\n");
    } else {
        printf("Test initlist head == NULL: FAIL\n");
    }

    if (l->tail == NULL) {
        printf("Test initlist tail == NULL: PASS\n");
    } else {
        printf("Test initlist tail == NULL: FAIL\n");
    }

    if (l->length == 0) {
        printf("Test initlist length == 0: PASS\n");
    } else {
        printf("Test initlist length == 0: FAIL\n");
    }
}

void test_single_append(struct intlist* l) {
    append(l, 1);

    if (l->head->value == 1) {
        printf("Test append to empty list head value 1: PASS\n");
    } else {
        printf("Test append to empty list head value 1: FAIL\n");
    }

    if (l->tail->value == 1) {
        printf("Test append to empty list tail value 1: PASS\n");
    } else {
        printf("Test append to empty list tail value 1: FAIL\n");
    }

    if (l->length == 1) {
        printf("Test append to empty list length == 1: PASS\n");
    } else {
        printf("Test append to empty list length == 1: FAIL\n");
    }
}

void test_multiple_append(struct intlist* l) {
    append(l, 2);
    append(l, 3);
    append(l, 4);

    if (l->head->value == 1) {
        printf("Test multiple appends list head value 1: PASS\n");
    } else {
        printf("Test multiple appends list head value 1: FAIL\n");
    }

    if (l->tail->value == 4) {
        printf("Test multiple appends list tail value 4: PASS\n");
    } else {
        printf("Test multiple appends list tail value 4: FAIL\n");
    }

    if (l->length == 4) {
        printf("Test multiple appends list length == 4: PASS\n");
    } else {
        printf("Test multiple appends list length == 4: FAIL\n");
    } 
}

int main(int argc, char* argv[]) {

    struct intlist* list;
    list = (struct intlist*)malloc(sizeof(struct intlist));
    if (list == NULL) {
        printf("Error allocating memory for list\n");
        exit(EXIT_FAILURE);
    }

    test_init(list);
    test_single_append(list);
    test_multiple_append(list);
}

