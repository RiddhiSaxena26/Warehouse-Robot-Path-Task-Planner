#include <stdio.h>
#include "warehouse.h"

// Breadth-First Search
void BFS(Graph* graph, int start) {

    if (graph == NULL || start < 0 || start >= graph->vertices) {
        printf("Invalid starting location!\n");
        return;
    }

    int visited[MAX_LOCATIONS] = {0};
    int queue[MAX_LOCATIONS];

    int front = 0;
    int rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS Traversal: ");

    while (front < rear) {

        int current = queue[front++];

        printf("%d ", current);

        Node* temp = graph->adjacencyList[current];

        while (temp != NULL) {

            int neighbour = temp->vertex;

            if (!visited[neighbour]) {

                visited[neighbour] = 1;
                queue[rear++] = neighbour;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}


// Recursive DFS helper
static void DFSRecursive(Graph* graph, int current, int visited[]) {

    visited[current] = 1;

    printf("%d ", current);

    Node* temp = graph->adjacencyList[current];

    while (temp != NULL) {

        int neighbour = temp->vertex;

        if (!visited[neighbour]) {
            DFSRecursive(graph, neighbour, visited);
        }

        temp = temp->next;
    }
}


// Depth-First Search
void DFS(Graph* graph, int start) {

    if (graph == NULL || start < 0 || start >= graph->vertices) {
        printf("Invalid starting location!\n");
        return;
    }

    int visited[MAX_LOCATIONS] = {0};

    printf("\nDFS Traversal: ");

    DFSRecursive(graph, start, visited);

    printf("\n");
}