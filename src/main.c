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

    freeGraph(warehouse);

    return 0;
}