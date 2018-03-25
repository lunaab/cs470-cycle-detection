/* intlist.h */

#ifndef __INTLIST__
#define __INTLIST__

struct node {
    struct node* next;
    int value;
};

struct intlist {
    struct node* head;
    struct node* tail;
    unsigned long length;
};

void initlist(struct intlist* l);
int append(struct intlist* l, int value);
int isempty(struct intlist* l);

#endif 
