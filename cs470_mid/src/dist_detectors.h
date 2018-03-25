/* Collection of Detection Algorithms */
/* See individual files for links to sources */

#ifndef __DETECTORS__
#define __DETECTORS__

#include <semaphore.h>

#include "intlist.h"
#include "graph.h"

struct dfs_args
{
    int rank;
    int start;
    int* cycle;
    struct Graph* g;
};

sem_t done;

int isCyclicUtil(struct Graph* g, int v, int* visited, int parent);

int dfsCycleDetection(struct Graph* g, int num_threads);

void* runDfsCycleDetection(void* args);

#endif 
