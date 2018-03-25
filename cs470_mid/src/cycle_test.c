#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "intlist.h"
#include "graph.h"
#include "detectors.h"

//int V = 10000;
//int V = 20000;
//int V = 40000;
int V = 80000;

void make_list(struct intlist* my_list) {
    //int loop_root = 0;
    //int loop_root = (V / 4) - 1;
    //int loop_root = (V / 2) - 1;
    //int loop_root = (V*3 / 4) - 1;
    int loop_root = V - 1;

    for (int i = 0; i < V; i++) {
        append(my_list, i);
    }
    
    struct node* looper = my_list->head;
    for (int i = 0; i < loop_root; i++) {
        looper = looper->next;
    }
    my_list->tail->next = looper;
    
}

void make_graph(struct Graph* my_graph) {
    //int loop_root = 0;
    //int loop_root = (V / 4) - 1;
    //int loop_root = (V / 2) - 1;
    //int loop_root = (V*3 / 4) - 1;
    int loop_root = V - 1;

    for (int i = 0; i < V-1; i++) {
        addEdge(my_graph, i, (i+1));
    }
    
    addEdge(my_graph, V-1, loop_root);
}

int main(int argc, char* argv[]) {

    struct intlist* my_list;
    my_list = (struct intlist*)malloc(sizeof(struct intlist));
    initlist(my_list);
    printf("Made List\n");
    
    
    struct Graph* my_graph;
    my_graph = createGraph(V);
    printf("Made Graph\n");
    
    
    struct timeval tv;
    double floyd_start, floyd_end;
    double brent_start, brent_end;
    double dfs_start, dfs_end;
    
    int floyd = 0;
    int brent = 0;
    int dfs = 0;
    
    make_list(my_list);
    make_graph(my_graph);
    
    gettimeofday(&tv, NULL);
    floyd_start = tv.tv_sec + (tv.tv_usec/1000000.0);
    floyd = floydCycleDetection(my_list);
    gettimeofday(&tv, NULL);
    floyd_end = tv.tv_sec + (tv.tv_usec/1000000.0);
    
    gettimeofday(&tv, NULL);
    brent_start = tv.tv_sec + (tv.tv_usec/1000000.0);
    brent = brentCycleDetection(my_list);
    gettimeofday(&tv, NULL);
    brent_end = tv.tv_sec + (tv.tv_usec/1000000.0);
    
    gettimeofday(&tv, NULL);
    dfs_start = tv.tv_sec + (tv.tv_usec/1000000.0);
    dfs = dfsCycleDetection(my_graph);
    gettimeofday(&tv, NULL);
    dfs_end = tv.tv_sec + (tv.tv_usec/1000000.0);
    
    printf("Floyd: %d, Brent: %d, DFS: %d\n", floyd, brent, dfs);
    printf("Floyd: %.5lfs, Brent: %.5lfs, DFS: %.5lfs\n",
           floyd_end-floyd_start, brent_end-brent_start, dfs_end-dfs_start);
}
