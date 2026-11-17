#include <stdio.h>
#include <limits.h>
#include "warehouse.h"

// Display robot information
void displayRobots(Robot robots[], int count) {

    printf("\n========== ROBOT STATUS ==========\n");

    printf("%-10s %-12s %-18s %-15s\n",
           "Robot ID", "Location", "Tasks Completed", "Distance");

    printf("----------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {

        printf("%-10d %-12d %-18d %-15d\n",
               robots[i].robotID,
               robots[i].location,
               robots[i].tasksCompleted,
               robots[i].totalDistance);
    }
}


// Greedy task assignment algorithm
void assignTasks(Graph* graph, Robot robots[], int robotCount,
                 Task tasks[], int taskCount) {

    if (graph == NULL || robots == NULL || tasks == NULL ||
        robotCount <= 0 || robotCount > MAX_ROBOTS ||
        taskCount < 0 || taskCount > MAX_TASKS) {

        printf("Invalid task assignment input!\n");
        return;
    }

    printf("\n========== GREEDY TASK ASSIGNMENT ==========\n");

    for (int i = 0; i < taskCount; i++) {

        int bestRobot = -1;
        int minimumDistance = INT_MAX;

        int pickup = tasks[i].pickup;
        int delivery = tasks[i].delivery;

        // Validate task locations
        if (pickup < 0 || pickup >= graph->vertices ||
            delivery < 0 || delivery >= graph->vertices) {

            printf("\nTask %d skipped: Invalid location.\n",
                   tasks[i].taskID);
            continue;
        }

        // Calculate pickup-to-delivery distance
        int deliveryDistance =
            getShortestDistance(graph, pickup, delivery);

        if (deliveryDistance == -1) {
            printf("\nTask %d skipped: Delivery is unreachable.\n",
                   tasks[i].taskID);
            continue;
        }

        // Find the closest robot
        for (int j = 0; j < robotCount; j++) {

            int distance = getShortestDistance(
                graph,
                robots[j].location,
                pickup
            );

            if (distance != -1 && distance < minimumDistance) {

                minimumDistance = distance;
                bestRobot = j;
            }
        }

        if (bestRobot == -1) {

            printf("\nTask %d could not be assigned.\n",
                   tasks[i].taskID);
            continue;
        }

        // Calculate total travel distance
        int travelDistance =
            minimumDistance + deliveryDistance;

        // Update robot information
        robots[bestRobot].totalDistance += travelDistance;
        robots[bestRobot].tasksCompleted++;

        robots[bestRobot].location = delivery;

        // Display assignment
        printf("\nTask %d assigned to Robot %d\n",
               tasks[i].taskID,
               robots[bestRobot].robotID);

        printf("Priority: %d\n", tasks[i].priority);

        printf("Pickup: %d | Delivery: %d\n",
               pickup, delivery);

        printf("Distance to Pickup: %d m\n",
               minimumDistance);

        printf("Delivery Distance: %d m\n",
               deliveryDistance);

        printf("Total Task Distance: %d m\n",
               travelDistance);
    }

    printf("\nAll possible tasks have been assigned.\n");
}