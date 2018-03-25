/* Depth first search cycle detection in undirected graph MPI */
/* Acquired at: https://www.geeksforgeeks.org/detect-cycle-undirected-graph/ */

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

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
            if (isCyclicUtil(node->dest, visited, v))
                return 1;
        }
        
        else if (node->dest != parent)
            return 1;
    }
    return 0;
}

void* run(void* args)
{
    //UNPACK ARGS
    //TODO
    // int start = ;
    // int stop = ;
    int cycle_found = 0;
    
    for (int u = start; u < stop; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(g, u, visited, -1))
             cycle_found = 1;
             
    return (void*)cycle_found;
}
 
// Returns true if the graph contains a cycle, else false.
int dfsCycleDetection(struct Graph* g, int num_threads)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    int *visited = (int*) malloc(g->V * sizeof(int));
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    
    pthread_t* workers = malloc(num_threads * sizeof(pthread_t));
    
    for (int i = 0; i < num_threads; i++) {
        //PREPARE ARGS
        //TODO
    
        pthread_create(&workers[i], NULL, run, NULL);
    }
 
}
