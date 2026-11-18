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
#define MAX_ROBOTS 10

// Robot structure
typedef struct Robot {
    int robotID;
    int location;
    int tasksCompleted;
    int totalDistance;
} Robot;

// Robot management
void displayRobots(Robot robots[], int count);

// Shortest distance calculation
int getShortestDistance(Graph* graph, int start, int destination);

// Greedy task assignment
void assignTasks(Graph* graph, Robot robots[], int robotCount,Task tasks[], int taskCount);

// Task sequence optimization
void greedyTaskOptimization(Graph* graph, Task tasks[],int taskCount, int startLocation);

void bruteForceTaskOptimization(Graph* graph, Task tasks[],int taskCount, int startLocation);

// Dynamic obstacle management
void blockPath(Graph* graph, int source, int destination);
void unblockPath(Graph* graph, int source, int destination);
void demonstrateReplanning(Graph* graph, int start, int destination);
// Multi-robot collision detection
void detectCollisions(
    int robot1Path[],
    int length1,
    int robot2Path[],
    int length2
);

void scheduleRobots(
    int robot1Path[],
    int length1,
    int robot2Path[],
    int length2
);

// Bellman-Ford shortest path algorithm
void bellmanFord(Graph* graph, int start, int destination);

// Compare Dijkstra and Bellman-Ford
void compareShortestPathAlgorithms(
    Graph* graph,
    int start,
    int destination
);

void demonstrateMergeSort(Task tasks[], int taskCount);


// Compare task optimization algorithms
void compareTaskOptimization(
    Graph* graph,
    Task tasks[],
    int taskCount,
    int startLocation
);


#endif