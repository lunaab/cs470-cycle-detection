/* Collection of Detection Algorithms */
/* See individual files for links to sources */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#include "intlist.h"
#include "dist_detectors.h"
#include "graph.h"

// A recursive function that uses visited[] and parent to detect
// cycle in subgraph reachable from vertex v.
int isCyclicUtil(struct Graph* g, int v, int* visited, int parent)
{
    // Mark the current node as visited
    visited[v] = 1;
    
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

void* runDfsCycleDetection(void* args) {
    
    int rank;
    int start;
    int* is_cycle;
    struct Graph* g;
    
    //Unpack args
    struct dfs_args* my_args = (struct dfs_args*)args;
    rank = my_args->rank;
    start = my_args->start;
    is_cycle = my_args->cycle;
    g = my_args->g;
    
    
    //printf("Thread %d unpacked with %d start\n", rank, start);
    
    // Mark all the vertices as not visited and not part of recursion
    // stack
    int *visited = (int*) malloc(g->V * sizeof(int));;
    //printf("Thread %d made visited\n", rank);
        
    for (int i = 0; i < g->V; i++)
       visited[i] = 0;
 
    // Call the recursive helper function to detect cycle in different
    // DFS trees
    
    for (int u = start; u < g->V; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(g, u, visited, -1))
             *is_cycle = 1;
             sem_post(&done);
             
    if (rank == 0) {
        sem_post(&done);
    }
    
    return NULL; 
}
 
// Returns true if the graph contains a cycle, else false.
int dfsCycleDetection(struct Graph* g, int num_threads)
{

    int is_cycle = 0;
    
    //struct dfs_args* my_args = (struct dfs_args*)malloc(num_threads * sizeof(struct dfs_args));
    struct dfs_args my_args [num_threads];
    pthread_t* workers = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    //done = sem_open("/done", O_CREAT, O_RDWR, 0);
    if (sem_init(&done, 0, 0) == -1) {
        printf("sem init failed\n");
    }
    for (int i = 0; i < num_threads; i++) {
        //prepare args
        my_args[i].rank = i;
        my_args[i].start = ((g->V) / num_threads) * i;
        my_args[i].cycle = &is_cycle;
        my_args[i].g = g;
        pthread_create(&workers[i], NULL, runDfsCycleDetection, (void*)&my_args[i]);
        pthread_detach(workers[i]);
    }
    
    //printf("Main thread sleeping\n");
    sem_wait(&done);
   
    return is_cycle;
}
