#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#define MAX_LOCATIONS 100

// Node representing a connected warehouse location
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Warehouse graph
typedef struct Graph {
    int vertices;
    Node* adjacencyList[MAX_LOCATIONS];
} Graph;

// Function declarations
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int source, int destination, int weight);
void displayGraph(Graph* graph);
void freeGraph(Graph* graph);

#endif