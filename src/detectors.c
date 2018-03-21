/* Collection of Detection Algorithms */
/* See individual files for links to sources */

#include <stdio.h>
#include <stdlib.h>

#include "intlist.h"
#include "detectors.h"
#include "graph.h"

int floydCycleDetection(struct intlist* list) {
    struct node* slow_p = list->head;
    struct node* fast_p = list->head;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p)
        {
            //printf("Found Loop");
            return 1;
        }
    }
    return 0;
}

int brentCycleDetection(struct intlist* list) {
    if (list->head == NULL) {
        return 0;
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
        return 0;
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

    return 1;
}

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
int isCyclicUtil(struct Graph* g, int v, int* visited, int parent)
{
    // Mark the current node as visited
    visited[v] = 1;
 
    /*// Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v))
              return 1;
        }
 
        // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
        else if (*i != parent)
           return 1;
    }*/
    
    struct AdjListNode* node = g->array[v].head;
    while (node != NULL) 
    {
        if (!visited[node->dest])
        {
            if (isCyclicUtil(g, node->dest, visited, v))
                return 1;
        }
        
        else if (node->dest != parent)
            return 1;
            
        node = node->next;
    }
    return 0;
}
 
// Returns true if the graph contains a cycle, else false.
int dfsCycleDetection(struct Graph* g)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    int *visited = (int*) malloc(g->V * sizeof(int));;
    for (int i = 0; i < g->V; i++)
        visited[i] = 0;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int u = 0; u < g->V; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(g, u, visited, -1))
             return 1;
 
    return 0;
}
