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
// Graph traversal algorithms
void BFS(Graph* graph, int start);
void DFS(Graph* graph, int start);
// Dijkstra's shortest path algorithm
void dijkstra(Graph* graph, int start, int destination);

#define MAX_TASKS 100

// Warehouse task structure
typedef struct Task {
    int taskID;
    int pickup;
    int delivery;
    int priority;
} Task;

// Task management functions
void displayTasks(Task tasks[], int n);
void mergeSort(Task tasks[], int left, int right);

#endif