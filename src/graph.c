#include <stdio.h>
#include <stdlib.h>
#include "warehouse.h"

// Create a new adjacency list node
Node* createNode(int vertex, int weight) {
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

// Create warehouse graph
Graph* createGraph(int vertices) {
    if (vertices <= 0 || vertices > MAX_LOCATIONS) {
        printf("Invalid number of locations!\n");
        return NULL;
    }

    Graph* graph = malloc(sizeof(Graph));

    if (graph == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    graph->vertices = vertices;

    for (int i = 0; i < MAX_LOCATIONS; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Add a bidirectional path
void addEdge(Graph* graph, int source, int destination, int weight) {
    if (graph == NULL ||
        source < 0 || source >= graph->vertices ||
        destination < 0 || destination >= graph->vertices ||
        source == destination || weight <= 0) {
        printf("Invalid warehouse path!\n");
        return;
    }

    Node* newNode = createNode(destination, weight);
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;

    newNode = createNode(source, weight);
    newNode->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = newNode;
}

// Display warehouse connections
void displayGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    printf("\n========== WAREHOUSE MAP ==========\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("\nLocation %d: ", i);

        Node* temp = graph->adjacencyList[i];

        while (temp != NULL) {
            printf("-> %d (%d m) ", temp->vertex, temp->weight);
            temp = temp->next;
        }

        printf("\n");
    }
}

// Free allocated memory
void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->vertices; i++) {
        Node* current = graph->adjacencyList[i];

        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }

    free(graph);
}