/* Adjacency list for undirected graph */
/* Acquired at: https://www.geeksforgeeks.org/graph-and-its-representations/ */

#ifndef __GRAPH__
#define __GRAPH__
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest);
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V);
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest);

#endif 
