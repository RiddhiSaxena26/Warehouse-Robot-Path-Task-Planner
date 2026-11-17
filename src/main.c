#include <stdio.h>
#include "warehouse.h"

int main() {

    Graph* warehouse = createGraph(6);

    if (warehouse == NULL) {
        return 1;
    }

    // Create warehouse paths
    addEdge(warehouse, 0, 1, 4);
    addEdge(warehouse, 0, 2, 2);
    addEdge(warehouse, 1, 3, 5);
    addEdge(warehouse, 2, 3, 3);
    addEdge(warehouse, 2, 4, 6);
    addEdge(warehouse, 3, 5, 2);
    addEdge(warehouse, 4, 5, 4);

    // Display warehouse
    displayGraph(warehouse);

    // BFS and DFS
    BFS(warehouse, 0);
    DFS(warehouse, 0);

    // Dijkstra's shortest path
    dijkstra(warehouse, 0, 5);
    // Warehouse tasks
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
    // Sort tasks according to priority
    mergeSort(tasks, 0, taskCount - 1);
    printf("\n========== TASKS SORTED BY PRIORITY ==========\n");
    displayTasks(tasks, taskCount);


    // Initialize warehouse robots
    Robot robots[] = {
        {1, 0, 0, 0},
        {2, 3, 0, 0},
        {3, 5, 0, 0}
    };
    int robotCount = sizeof(robots) / sizeof(robots[0]);
    // Display initial robot position
    printf("\n========== INITIAL ROBOT POSITIONS ==========\n");
    displayRobots(robots, robotCount);
    // Assign tasks using greedy algorithm
    assignTasks(warehouse, robots, robotCount, tasks, taskCount);
    // Display updated robot information
    printf("\n========== FINAL ROBOT STATUS ==========\n");
    displayRobots(robots, robotCount);
    
    freeGraph(warehouse);

    return 0;
}