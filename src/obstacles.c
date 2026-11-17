#include <stdio.h>
#include <stdlib.h>
#include "warehouse.h"
// Store the original warehouse paths
typedef struct {
    int source;
    int destination;
    int weight;
} WarehousePath;

static WarehousePath blockedPaths[100];
static int blockedCount = 0;

// Find a blocked path
static int findBlockedPath(int source, int destination) {

    for (int i = 0; i < blockedCount; i++) {

        if ((blockedPaths[i].source == source &&
             blockedPaths[i].destination == destination) ||
            (blockedPaths[i].source == destination &&
             blockedPaths[i].destination == source)) {

            return i;
        }
    }

    return -1;
}

// Remove a connection from one adjacency list
static int removeConnection(Graph* graph, int source,
                            int destination) {

    Node* current = graph->adjacencyList[source];
    Node* previous = NULL;

    while (current != NULL) {

        if (current->vertex == destination) {

            int weight = current->weight;

            if (previous == NULL) {
                graph->adjacencyList[source] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);

            return weight;
        }

        previous = current;
        current = current->next;
    }

    return -1;
}

// Block a warehouse path
void blockPath(Graph* graph, int source, int destination) {

    if (graph == NULL ||
        source < 0 || source >= graph->vertices ||
        destination < 0 || destination >= graph->vertices ||
        source == destination) {

        printf("\nInvalid path!\n");
        return;
    }

    if (findBlockedPath(source, destination) != -1) {
        printf("\nThis path is already blocked.\n");
        return;
    }

    if (blockedCount >= 100) {
        printf("\nBlocked path storage is full.\n");
        return;
    }

    int weight = removeConnection(graph, source, destination);

    if (weight == -1) {
        printf("\nPath does not exist!\n");
        return;
    }

    removeConnection(graph, destination, source);

    blockedPaths[blockedCount].source = source;
    blockedPaths[blockedCount].destination = destination;
    blockedPaths[blockedCount].weight = weight;

    blockedCount++;

    printf("\nPath %d <-> %d has been BLOCKED.\n",
           source, destination);
}

// Restore a blocked path
void unblockPath(Graph* graph, int source, int destination) {

    if (graph == NULL) {
        return;
    }

    int index = findBlockedPath(source, destination);

    if (index == -1) {
        printf("\nThis path is not blocked.\n");
        return;
    }

    addEdge(
        graph,
        blockedPaths[index].source,
        blockedPaths[index].destination,
        blockedPaths[index].weight
    );

    for (int i = index; i < blockedCount - 1; i++) {
        blockedPaths[i] = blockedPaths[i + 1];
    }

    blockedCount--;

    printf("\nPath %d <-> %d has been RESTORED.\n",
           source, destination);
}

// Demonstrate dynamic path replanning
void demonstrateReplanning(Graph* graph, int start,
                           int destination) {

    printf("\n========================================\n");
    printf("       DYNAMIC PATH REPLANNING\n");
    printf("========================================\n");

    printf("\nOriginal Shortest Path:\n");

    dijkstra(graph, start, destination);

    printf("\nBlocking path between locations 2 and 3...\n");

    blockPath(graph, 2, 3);

    printf("\nRecalculating shortest path...\n");

    dijkstra(graph, start, destination);

    printf("\nRestoring the blocked path...\n");

    unblockPath(graph, 2, 3);

    printf("\nShortest path after restoration:\n");

    dijkstra(graph, start, destination);
}