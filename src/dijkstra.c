#include <stdio.h>
#include <limits.h>
#include "warehouse.h"

#define INF INT_MAX

void dijkstra(Graph* graph, int start, int destination) {

    if (graph == NULL ||
        start < 0 || start >= graph->vertices ||
        destination < 0 || destination >= graph->vertices) {

        printf("Invalid location!\n");
        return;
    }

    int distance[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS] = {0};
    int parent[MAX_LOCATIONS];

    // Initialize distances
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[start] = 0;

    // Find shortest distances
    for (int i = 0; i < graph->vertices; i++) {

        int minDistance = INF;
        int current = -1;

        // Find unvisited vertex with minimum distance
        for (int j = 0; j < graph->vertices; j++) {

            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                current = j;
            }
        }

        if (current == -1) {
            break;
        }

        visited[current] = 1;

        if (current == destination) {
            break;
        }

        // Update neighbouring distances
        Node* temp = graph->adjacencyList[current];

        while (temp != NULL) {

            int neighbour = temp->vertex;
            int weight = temp->weight;

            if (!visited[neighbour] &&
                distance[current] <= INT_MAX - weight &&
                distance[current] + weight < distance[neighbour]) {

                distance[neighbour] = distance[current] + weight;
                parent[neighbour] = current;
            }

            temp = temp->next;
        }
    }

    // Display result
    if (distance[destination] == INF) {

        printf("\nNo path exists between locations %d and %d.\n",
               start, destination);
        return;
    }

    printf("\n========== SHORTEST PATH ==========\n");

    printf("Starting Location: %d\n", start);
    printf("Destination: %d\n", destination);
    printf("Minimum Distance: %d metres\n", distance[destination]);

    // Reconstruct shortest path
    int path[MAX_LOCATIONS];
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    printf("Shortest Route: ");

    for (int i = count - 1; i >= 0; i--) {

        printf("%d", path[i]);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\n");

    // Return shortest distance between two locations
int getShortestDistance(Graph* graph, int start, int destination) {

    if (graph == NULL ||
        start < 0 || start >= graph->vertices ||
        destination < 0 || destination >= graph->vertices) {
        return -1;
    }

    int distance[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS] = {0};

    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INT_MAX;
    }

    distance[start] = 0;

    for (int i = 0; i < graph->vertices; i++) {

        int minDistance = INT_MAX;
        int current = -1;

        // Find closest unvisited location
        for (int j = 0; j < graph->vertices; j++) {

            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                current = j;
            }
        }

        if (current == -1) {
            break;
        }

        if (current == destination) {
            return distance[current];
        }

        visited[current] = 1;

        Node* temp = graph->adjacencyList[current];

        while (temp != NULL) {

            int neighbour = temp->vertex;
            int weight = temp->weight;

            if (!visited[neighbour] &&
                distance[current] <= INT_MAX - weight &&
                distance[current] + weight < distance[neighbour]) {

                distance[neighbour] = distance[current] + weight;
            }

            temp = temp->next;
        }
    }

    // Destination is unreachable
    return -1;
}