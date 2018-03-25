#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "graph.h"
#include "dist_detectors.h"

//int V = 10000;
//int V = 20000;
//int V = 40000;
int V = 80000;

//int T = 1;
//int T = 2;
//int T = 4;
int T = 8;

void make_graph(struct Graph* my_graph) {
    int loop_root = 0;
    //int loop_root = (V / 4) - 1;
    //int loop_root = (V / 2) - 1;
    //int loop_root = (V*3 / 4) - 1;
    //int loop_root = V - 1;

    for (int i = 0; i < V-1; i++) {
        addEdge(my_graph, i, (i+1));
    }
    
    addEdge(my_graph, V-1, loop_root);
}

int main(int argc, char* argv[]) {
    
    struct Graph* my_graph;
    my_graph = createGraph(V);
    
    struct timeval tv;
    double dfs_start, dfs_end;
    
    int dfs = 0;
    
    make_graph(my_graph);
    
    gettimeofday(&tv, NULL);
    dfs_start = tv.tv_sec + (tv.tv_usec/1000000.0);
    dfs = dfsCycleDetection(my_graph, T);
    gettimeofday(&tv, NULL);
    dfs_end = tv.tv_sec + (tv.tv_usec/1000000.0); 
       
    printf("DFS: %d\n", dfs);
    printf("DFS TIME: %.5lfs\n", dfs_end-dfs_start);
}
