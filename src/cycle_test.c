#include <stdio.h>
#include <stdlib.h>

#include "intlist.h"
#include "graph.h"
#include "detectors.h"

int V = 6;

void make_list(struct intlist* my_list) {
    for (int i = 0; i < V; i++) {
        append(my_list, i);
    }
    
    my_list->tail->next = my_list->head;
    
}

void make_graph(struct Graph* my_graph) {
    for (int i = 0; i < V; i++) {
        addEdge(my_graph, i, (i+1) % V);
    }
}

int main(int argc, char* argv[]) {

    struct intlist* my_list;
    initlist(my_list);
    printf("Made List\n");
    
    struct Graph* my_graph;
    my_graph = createGraph(V);
    printf("Made Graph\n");
    
    
    int floyd = 0;
    int brent = 0;
    int dfs = 0;
    
    make_list(my_list);
    make_graph(my_graph);
    
    printf("Starting Floyd\n");
    floyd = floydCycleDetection(my_list);
    printf("Finished Floyd\n");
    printf("Starting Brent\n");
    brent = brentCycleDetection(my_list);
    printf("Finished Brent\n");
    printf("Starting DFS\n");
    dfs = dfsCycleDetection(my_graph);
    printf("Finished DFS\n");
    
    printf("Floyd: %d, Brent: %d, DFS: %d\n", floyd, brent, dfs);
}
