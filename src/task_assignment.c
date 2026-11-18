
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <limits.h>
#include "warehouse.h"

// ==========================================
// DISPLAY ROBOT INFORMATION
// ==========================================

void displayRobots(Robot robots[], int count) {

    if (robots == NULL || count <= 0) {
        printf("\nNo robots available.\n");
        return;
    }

    printf("\n%-10s %-12s %-18s %-15s\n",
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


// ==========================================
// GREEDY ROBOT TASK ASSIGNMENT
// ==========================================

void assignTasks(
    Graph* graph,
    Robot robots[],
    int robotCount,
    Task tasks[],
    int taskCount
) {

    if (graph == NULL || robots == NULL || tasks == NULL ||
        robotCount <= 0 || robotCount > MAX_ROBOTS ||
        taskCount <= 0 || taskCount > MAX_TASKS) {

        printf("\nInvalid task assignment input!\n");
        return;
    }

    int assignedCount = 0;
    int skippedCount = 0;
    int64_t totalWarehouseDistance = 0;

    printf("\n==================================================\n");
    printf("           ROBOT TASK ASSIGNMENT\n");
    printf("==================================================\n");

    printf("Algorithm Used: Greedy Task Assignment\n");
    printf("Technique: Greedy Method\n");
    printf("Supporting Algorithm: Dijkstra's Shortest Path\n");
    printf("Selection Rule: Nearest Robot to Pickup Location\n");
    printf("Task Order: Highest Priority First\n");

    printf("\nTotal Robots: %d\n", robotCount);
    printf("Total Tasks: %d\n", taskCount);

    printf("\n--------------------------------------------------\n");
    printf("                TASK ALLOCATION\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < taskCount; i++) {

        int bestRobot = -1;
        int minimumDistance = INT_MAX;

        int pickup = tasks[i].pickup;
        int delivery = tasks[i].delivery;

        if (pickup < 0 || pickup >= graph->vertices ||
            delivery < 0 || delivery >= graph->vertices) {

            printf("\nTask %d skipped: Invalid location.\n",
                   tasks[i].taskID);

            skippedCount++;
            continue;
        }

        int deliveryDistance = getShortestDistance(
            graph, pickup, delivery
        );

        if (deliveryDistance == -1) {

            printf("\nTask %d skipped: Delivery unreachable.\n",
                   tasks[i].taskID);

            skippedCount++;
            continue;
        }

        // Find the robot nearest to the pickup location
        for (int j = 0; j < robotCount; j++) {

            int distance = getShortestDistance(
                graph,
                robots[j].location,
                pickup
            );

            if (distance != -1 &&
                distance < minimumDistance) {

                minimumDistance = distance;
                bestRobot = j;
            }
        }

        if (bestRobot == -1) {

            printf("\nTask %d skipped: No robot can reach pickup.\n",
                   tasks[i].taskID);

            skippedCount++;
            continue;
        }

        // Prevent integer overflow
        if (minimumDistance > INT_MAX - deliveryDistance) {

            printf("\nTask %d skipped: Distance overflow.\n",
                   tasks[i].taskID);

            skippedCount++;
            continue;
        }

        int travelDistance =
            minimumDistance + deliveryDistance;

        if (robots[bestRobot].totalDistance >
            INT_MAX - travelDistance) {

            printf("\nTask %d skipped: Robot distance limit reached.\n",
                   tasks[i].taskID);

            skippedCount++;
            continue;
        }

        int previousLocation = robots[bestRobot].location;

        // Update selected robot
        robots[bestRobot].totalDistance += travelDistance;
        robots[bestRobot].tasksCompleted++;
        robots[bestRobot].location = delivery;

        totalWarehouseDistance += travelDistance;
        assignedCount++;

        printf("\nTask ID: %d\n", tasks[i].taskID);
        printf("Priority: %d\n", tasks[i].priority);
        printf("Assigned Robot: %d\n",
               robots[bestRobot].robotID);

        printf("Robot Starting Location: %d\n",
               previousLocation);

        printf("Pickup Location: %d\n", pickup);
        printf("Delivery Location: %d\n", delivery);

        printf("Distance to Pickup: %d metres\n",
               minimumDistance);

        printf("Pickup to Delivery: %d metres\n",
               deliveryDistance);

        printf("Total Task Distance: %d metres\n",
               travelDistance);

        printf("----------------------------------------\n");
    }

    // ==========================================
    // ASSIGNMENT SUMMARY
    // ==========================================

    printf("\n==================================================\n");
    printf("             ASSIGNMENT SUMMARY\n");
    printf("==================================================\n");

    printf("Total Tasks: %d\n", taskCount);
    printf("Successfully Assigned: %d\n", assignedCount);
    printf("Unassigned Tasks: %d\n", skippedCount);

    printf("Total Planned Warehouse Distance: %I64d metres\n",totalWarehouseDistance);

    printf("\nFinal Robot Status:\n");
    displayRobots(robots, robotCount);

    printf("\nTime Complexity: O(T * (R + 1) * (V^2 + E))\n");
    printf("Auxiliary Space Complexity: O(V)\n");

    printf("\nNote: Greedy assignment does not guarantee\n");
    printf("the globally minimum travel distance.\n");

    printf("==================================================\n");
}