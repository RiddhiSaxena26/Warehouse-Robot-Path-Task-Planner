#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "warehouse.h"

#define INF INT_MAX

// ==========================================
// BELLMAN-FORD ALGORITHM
// ==========================================

void bellmanFord(Graph* graph, int start, int destination) {

    if (graph == NULL ||
        start < 0 || start >= graph->vertices ||
        destination < 0 || destination >= graph->vertices) {

        printf("\nInvalid location!\n");
        return;
    }

    int distance[MAX_LOCATIONS];
    int parent[MAX_LOCATIONS];

    // Initialize distances
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[start] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i < graph->vertices; i++) {

        int updated = 0;

        for (int u = 0; u < graph->vertices; u++) {

            Node* temp = graph->adjacencyList[u];

            while (temp != NULL) {

                int v = temp->vertex;
                int weight = temp->weight;

                if (distance[u] != INF) {

                    long long newDistance =
                        (long long)distance[u] + weight;

                    if (newDistance >= INT_MIN &&
                        newDistance < distance[v]) {

                        distance[v] = (int)newDistance;
                        parent[v] = u;
                        updated = 1;
                    }
                }

                temp = temp->next;
            }
        }

        // Stop if no distances changed
        if (!updated) {
            break;
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < graph->vertices; u++) {

        Node* temp = graph->adjacencyList[u];

        while (temp != NULL) {

            int v = temp->vertex;

            if (distance[u] != INF &&
                (long long)distance[u] + temp->weight
                    < distance[v]) {

                printf("\nNegative-weight cycle detected!\n");
                return;
            }

            temp = temp->next;
        }
    }

    // Check reachability
    if (distance[destination] == INF) {

        printf("\nDestination is unreachable.\n");
        return;
    }

    printf("\n========== BELLMAN-FORD RESULT ==========\n");

    printf("Starting Location: %d\n", start);
    printf("Destination: %d\n", destination);

    printf("Minimum Distance: %d metres\n",
           distance[destination]);

    // Reconstruct shortest path
    int path[MAX_LOCATIONS];
    int count = 0;
    int current = destination;

    while (current != -1 && count < MAX_LOCATIONS) {

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
}


// ==========================================
// ALGORITHM PERFORMANCE COMPARISON
// ==========================================

void compareShortestPathAlgorithms(
    Graph* graph,
    int start,
    int destination
) {

    if (graph == NULL ||
        start < 0 || start >= graph->vertices ||
        destination < 0 || destination >= graph->vertices) {

        printf("\nInvalid comparison input.\n");
        return;
    }

    printf("\n========================================\n");
    printf("   SHORTEST PATH ALGORITHM COMPARISON\n");
    printf("========================================\n");

    clock_t startTime;
    clock_t endTime;

    double dijkstraTime;
    double bellmanTime;

    // Measure Dijkstra
    startTime = clock();

    dijkstra(graph, start, destination);

    endTime = clock();

    dijkstraTime =
        (double)(endTime - startTime) / CLOCKS_PER_SEC;

    // Measure Bellman-Ford
    startTime = clock();

    bellmanFord(graph, start, destination);

    endTime = clock();

    bellmanTime =
        (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("\n========== PERFORMANCE RESULTS ==========\n");

    printf("Dijkstra Execution Time: %.8f seconds\n",
           dijkstraTime);

    printf("Bellman-Ford Execution Time: %.8f seconds\n",
           bellmanTime);

    printf("\nTheoretical Time Complexity:\n");

    printf("Dijkstra: O(V^2 + E)\n");
    printf("Bellman-Ford: O(VE)\n");
}