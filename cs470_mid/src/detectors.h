/* Collection of Detection Algorithms */
/* See individual files for links to sources */

#ifndef __DETECTORS__
#define __DETECTORS__

#include "intlist.h"
#include "graph.h"

int floydCycleDetection(struct intlist* list);

int brentCycleDetection(struct intlist* list);

int isCyclicUtil(struct Graph* g, int v, int* visited, int parent);

int dfsCycleDetection(struct Graph* g);

#endif 
