/* Depth first search cycle detection in undirected graph */
/* Acquired at: https://www.geeksforgeeks.org/detect-cycle-undirected-graph/ */

#include <stdio.h>
#include <stdlib.h>

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
int isCyclicUtil(struct graph* g, int v, int* visited, int parent)
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
 
// Returns true if the graph contains a cycle, else false.
int dfsCycleDetection(struct graph* g)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    int *visited = (int*) malloc(g->V * sizeof(int));;
    for (int i = 0; i < V; i++)
        visited[i] = 0;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int u = 0; u < V; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(g, u, visited, -1))
             return 1;
 
    return 0;
}
