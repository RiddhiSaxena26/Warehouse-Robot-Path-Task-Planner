#include <stdio.h>
#include "warehouse.h"

int main() {

    // =================================================
    // CREATE WAREHOUSE GRAPH
    // =================================================

    Graph* warehouse = createGraph(6);

    if (warehouse == NULL) {
        return 1;
    }

    // Warehouse paths
    addEdge(warehouse, 0, 1, 4);
    addEdge(warehouse, 0, 2, 2);
    addEdge(warehouse, 1, 3, 5);
    addEdge(warehouse, 2, 3, 3);
    addEdge(warehouse, 2, 4, 6);
    addEdge(warehouse, 3, 5, 2);
    addEdge(warehouse, 4, 5, 4);


    // =================================================
    // DISPLAY WAREHOUSE GRAPH
    // =================================================

    displayGraph(warehouse);


    // =================================================
    // BFS AND DFS
    // =================================================

    BFS(warehouse, 0);

    DFS(warehouse, 0);


    // =================================================
    // DIJKSTRA SHORTEST PATH
    // =================================================

    dijkstra(warehouse, 0, 5);


    // =================================================
    // WAREHOUSE TASK MANAGEMENT
    // =================================================

    Task tasks[] = {
        {101, 2, 5, 3},
        {102, 1, 4, 1},
        {103, 3, 0, 5},
        {104, 4, 2, 2},
        {105, 5, 1, 4}
    };

    int taskCount = sizeof(tasks) / sizeof(tasks[0]);

    printf("\n========== ORIGINAL TASKS ==========\n");

    displayTasks(tasks, taskCount);


    // =================================================
    // MERGE SORT TASK PRIORITIES
    // =================================================

    mergeSort(tasks, 0, taskCount - 1);

    printf("\n========== SORTED TASKS ==========\n");

    displayTasks(tasks, taskCount);


    // =================================================
    // INITIALIZE ROBOTS
    // =================================================

    Robot robots[] = {
        {1, 0, 0, 0},
        {2, 3, 0, 0},
        {3, 5, 0, 0}
    };

    int robotCount = sizeof(robots) / sizeof(robots[0]);

    printf("\n========== INITIAL ROBOTS ==========\n");

    displayRobots(robots, robotCount);


    // =================================================
    // GREEDY ROBOT TASK ASSIGNMENT
    // =================================================

    assignTasks(
        warehouse,
        robots,
        robotCount,
        tasks,
        taskCount
    );


    // =================================================
    // FINAL ROBOT STATUS
    // =================================================

    printf("\n========== FINAL ROBOT STATUS ==========\n");

    displayRobots(robots, robotCount);


    // =================================================
    // TASK SEQUENCE OPTIMIZATION
    // =================================================

    Task optimizationTasks[] = {
        {101, 2, 5, 3},
        {102, 1, 4, 1},
        {103, 3, 0, 5}
    };

    int optimizationCount =
        sizeof(optimizationTasks) /
        sizeof(optimizationTasks[0]);

    printf("\n========== TASK SEQUENCE COMPARISON ==========\n");

    // Greedy optimization
    greedyTaskOptimization(
        warehouse,
        optimizationTasks,
        optimizationCount,
        0
    );

    // Brute force optimization
    bruteForceTaskOptimization(
        warehouse,
        optimizationTasks,
        optimizationCount,
        0
    );


    // =================================================
    // FREE MEMORY
    // =================================================

    freeGraph(warehouse);

    printf("\nProgram executed successfully.\n");

    return 0;
}