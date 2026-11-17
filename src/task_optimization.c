#include <stdio.h>
#include <limits.h>
#include "warehouse.h"

#define MAX_OPT_TASKS 8

// Calculate the distance required to complete one task
static int calculateTaskDistance(
    Graph* graph,
    int currentLocation,
    Task task
) {
    int pickupDistance = getShortestDistance(
        graph, currentLocation, task.pickup
    );

    int deliveryDistance = getShortestDistance(
        graph, task.pickup, task.delivery
    );

    if (pickupDistance == -1 || deliveryDistance == -1) {
        return -1;
    }

    if (pickupDistance > INT_MAX - deliveryDistance) {
        return -1;
    }

    return pickupDistance + deliveryDistance;
}


// ==========================================
// GREEDY TASK OPTIMIZATION
// ==========================================

void greedyTaskOptimization(
    Graph* graph,
    Task tasks[],
    int taskCount,
    int startLocation
) {
    if (graph == NULL || tasks == NULL ||
        taskCount <= 0 || taskCount > MAX_TASKS ||
        startLocation < 0 || startLocation >= graph->vertices) {

        printf("\nInvalid greedy optimization input.\n");
        return;
    }

    int visited[MAX_TASKS] = {0};
    int currentLocation = startLocation;
    int totalDistance = 0;
    int order[MAX_TASKS];

    printf("\n========== GREEDY TASK OPTIMIZATION ==========\n");
    printf("Starting Location: %d\n", startLocation);

    for (int i = 0; i < taskCount; i++) {

        int bestTask = -1;
        int minimumPickupDistance = INT_MAX;

        for (int j = 0; j < taskCount; j++) {

            if (visited[j]) {
                continue;
            }

            int pickupDistance = getShortestDistance(
                graph, currentLocation, tasks[j].pickup
            );

            int taskDistance = calculateTaskDistance(
                graph, currentLocation, tasks[j]
            );

            if (taskDistance != -1 &&
                pickupDistance < minimumPickupDistance) {

                minimumPickupDistance = pickupDistance;
                bestTask = j;
            }
        }

        if (bestTask == -1) {
            printf("Some tasks are unreachable.\n");
            return;
        }

        int distance = calculateTaskDistance(
            graph, currentLocation, tasks[bestTask]
        );

        if (totalDistance > INT_MAX - distance) {
            printf("Distance overflow detected.\n");
            return;
        }

        totalDistance += distance;
        visited[bestTask] = 1;
        order[i] = bestTask;

        printf(
            "Task %d: %d -> %d -> %d | Distance: %d m\n",
            tasks[bestTask].taskID,
            currentLocation,
            tasks[bestTask].pickup,
            tasks[bestTask].delivery,
            distance
        );

        currentLocation = tasks[bestTask].delivery;
    }

    printf("\nGreedy Task Order: ");

    for (int i = 0; i < taskCount; i++) {
        printf("%d", tasks[order[i]].taskID);

        if (i < taskCount - 1) {
            printf(" -> ");
        }
    }

    printf("\nTotal Greedy Distance: %d metres\n", totalDistance);
}


// ==========================================
// BRUTE FORCE TASK OPTIMIZATION
// ==========================================

static int bestDistance;
static int bestOrder[MAX_OPT_TASKS];
static int currentOrder[MAX_OPT_TASKS];

static void findBestOrder(
    Graph* graph,
    Task tasks[],
    int taskCount,
    int depth,
    int currentLocation,
    int currentDistance,
    int visited[]
) {
    if (depth == taskCount) {

        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;

            for (int i = 0; i < taskCount; i++) {
                bestOrder[i] = currentOrder[i];
            }
        }

        return;
    }

    for (int i = 0; i < taskCount; i++) {

        if (visited[i]) {
            continue;
        }

        int distance = calculateTaskDistance(
            graph, currentLocation, tasks[i]
        );

        if (distance == -1) {
            continue;
        }

        if (currentDistance > INT_MAX - distance) {
            continue;
        }

        int newDistance = currentDistance + distance;

        // Skip paths that cannot improve the best result
        if (newDistance >= bestDistance) {
            continue;
        }

        visited[i] = 1;
        currentOrder[depth] = i;

        findBestOrder(
            graph,
            tasks,
            taskCount,
            depth + 1,
            tasks[i].delivery,
            newDistance,
            visited
        );

        visited[i] = 0;
    }
}


void bruteForceTaskOptimization(
    Graph* graph,
    Task tasks[],
    int taskCount,
    int startLocation
) {
    if (graph == NULL || tasks == NULL ||
        taskCount <= 0 || taskCount > MAX_OPT_TASKS ||
        startLocation < 0 || startLocation >= graph->vertices) {

        printf("\nBrute force supports 1 to %d tasks.\n",
               MAX_OPT_TASKS);
        return;
    }

    int visited[MAX_OPT_TASKS] = {0};

    bestDistance = INT_MAX;

    findBestOrder(
        graph,
        tasks,
        taskCount,
        0,
        startLocation,
        0,
        visited
    );

    printf("\n========== BRUTE FORCE OPTIMIZATION ==========\n");

    if (bestDistance == INT_MAX) {
        printf("No valid task sequence exists.\n");
        return;
    }

    printf("Starting Location: %d\n", startLocation);
    printf("Optimal Task Order: ");

    for (int i = 0; i < taskCount; i++) {

        printf("%d", tasks[bestOrder[i]].taskID);

        if (i < taskCount - 1) {
            printf(" -> ");
        }
    }

    printf("\nMinimum Total Distance: %d metres\n", bestDistance);
}