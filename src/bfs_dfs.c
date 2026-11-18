#include <stdio.h>
#include "warehouse.h"

// ==========================================
// BREADTH-FIRST SEARCH (BFS)
// ==========================================

void BFS(Graph* graph, int start) {

    if (graph == NULL || start < 0 || start >= graph->vertices) {
        printf("\nInvalid starting location!\n");
        return;
    }

    int visited[MAX_LOCATIONS] = {0};
    int queue[MAX_LOCATIONS];

    int front = 0;
    int rear = 0;
    int locationsVisited = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\n========================================\n");
    printf("       WAREHOUSE GRAPH TRAVERSAL\n");
    printf("========================================\n");

    printf("Algorithm Used: Breadth-First Search (BFS)\n");
    printf("Technique: Graph Traversal\n");
    printf("Data Structure: Queue (FIFO)\n\n");

    printf("Starting Location: %d\n", start);
    printf("Traversal Order: ");

    while (front < rear) {

        int current = queue[front++];
        locationsVisited++;

        printf("%d", current);

        Node* temp = graph->adjacencyList[current];

        while (temp != NULL) {

            int neighbour = temp->vertex;

            if (!visited[neighbour]) {
                visited[neighbour] = 1;
                queue[rear++] = neighbour;
            }

            temp = temp->next;
        }

        if (front < rear) {
            printf(" -> ");
        }
    }

    printf("\nLocations Visited: %d\n", locationsVisited);

    printf("\nTime Complexity: O(V + E)\n");
    printf("Auxiliary Space Complexity: O(V)\n");

    printf("========================================\n");
}


// ==========================================
// DEPTH-FIRST SEARCH (DFS)
// ==========================================

static void DFSRecursive(
    Graph* graph,
    int current,
    int visited[],
    int* locationsVisited
) {

    visited[current] = 1;
    (*locationsVisited)++;

    printf("%d", current);

    Node* temp = graph->adjacencyList[current];

    while (temp != NULL) {

        int neighbour = temp->vertex;

        if (!visited[neighbour]) {
            printf(" -> ");

            DFSRecursive(
                graph,
                neighbour,
                visited,
                locationsVisited
            );
        }

        temp = temp->next;
    }
}


void DFS(Graph* graph, int start) {

    if (graph == NULL || start < 0 || start >= graph->vertices) {
        printf("\nInvalid starting location!\n");
        return;
    }

    int visited[MAX_LOCATIONS] = {0};
    int locationsVisited = 0;

    printf("\n========================================\n");
    printf("       WAREHOUSE GRAPH TRAVERSAL\n");
    printf("========================================\n");

    printf("Algorithm Used: Depth-First Search (DFS)\n");
    printf("Technique: Graph Traversal\n");
    printf("Data Structure: Recursion (Call Stack)\n\n");

    printf("Starting Location: %d\n", start);
    printf("Traversal Order: ");

    DFSRecursive(
        graph,
        start,
        visited,
        &locationsVisited
    );

    printf("\nLocations Visited: %d\n", locationsVisited);

    printf("\nTime Complexity: O(V + E)\n");
    printf("Auxiliary Space Complexity: O(V)\n");

    printf("========================================\n");
}