#include <stdio.h>
#include "warehouse.h"

#define MAX_TIME 100

// Get robot position at a particular time
static int getPosition(int path[], int length, int time) {

    if (time < length) {
        return path[time];
    }

    // Robot remains at its final location
    return path[length - 1];
}


// ==========================================
// COLLISION DETECTION
// ==========================================

void detectCollisions(
    int robot1Path[],
    int length1,
    int robot2Path[],
    int length2
) {

    if (robot1Path == NULL || robot2Path == NULL ||
        length1 <= 0 || length2 <= 0 ||
        length1 > MAX_TIME || length2 > MAX_TIME) {

        printf("\nInvalid robot paths.\n");
        return;
    }

    printf("\n========== COLLISION DETECTION ==========\n");

    int maxLength = length1 > length2 ? length1 : length2;
    int collisionFound = 0;

    for (int t = 0; t < maxLength; t++) {

        int pos1 = getPosition(robot1Path, length1, t);
        int pos2 = getPosition(robot2Path, length2, t);

        // Vertex conflict
        if (pos1 == pos2) {

            printf(
                "\nVertex Conflict at time %d: "
                "Both robots at Location %d\n",
                t, pos1
            );

            collisionFound = 1;
        }

        // Edge conflict
        if (t < maxLength - 1) {

            int next1 = getPosition(robot1Path, length1, t + 1);
            int next2 = getPosition(robot2Path, length2, t + 1);

            if (pos1 == next2 &&
                pos2 == next1 &&
                pos1 != pos2) {

                printf(
                    "\nEdge Conflict between time %d and %d: "
                    "Robots swap Locations %d and %d\n",
                    t, t + 1, pos1, pos2
                );

                collisionFound = 1;
            }
        }
    }

    if (!collisionFound) {
        printf("\nNo collisions detected.\n");
    }
}


// ==========================================
// SIMPLE ROBOT SCHEDULING
// ==========================================

void scheduleRobots(
    int robot1Path[],
    int length1,
    int robot2Path[],
    int length2
) {
    if (robot1Path == NULL || robot2Path == NULL ||
        length1 <= 0 || length2 <= 0 ||
        length1 > 100 || length2 > 100) {
        printf("\nInvalid robot paths.\n");
        return;
    }

    printf("\n========================================\n");
    printf("       ROBOT MOVEMENT SCHEDULING\n");
    printf("========================================\n");

    printf("Method: Sequential Scheduling\n");
    printf("Technique: Time-Step Scheduling\n\n");

    // Check whether Robot 2's waiting location
    // appears anywhere on Robot 1's route.
    for (int i = 0; i < length1; i++) {
        if (robot1Path[i] == robot2Path[0]) {
            printf("Unsafe schedule detected!\n");
            printf("Robot 2 is waiting on Robot 1's route.\n");
            printf("A different route or waiting location is required.\n");
            return;
        }
    }

    // Check whether Robot 1's final location
    // appears anywhere on Robot 2's route.
    for (int i = 0; i < length2; i++) {
        if (robot2Path[i] == robot1Path[length1 - 1]) {
            printf("Unsafe schedule detected!\n");
            printf("Robot 1's final location blocks Robot 2's route.\n");
            printf("A different route or waiting location is required.\n");
            return;
        }
    }

    int totalTime = length1 + length2 - 2;

    printf("Robot 1 moves first.\n");
    printf("Robot 2 waits until Robot 1 finishes.\n\n");

    printf("%-10s %-15s %-15s\n",
           "Time", "Robot 1", "Robot 2");

    for (int t = 0; t <= totalTime; t++) {

        int pos1 = t < length1
                   ? robot1Path[t]
                   : robot1Path[length1 - 1];

        int robot2Time = t - (length1 - 1);

        int pos2 = robot2Time < 0
                   ? robot2Path[0]
                   : robot2Time < length2
                     ? robot2Path[robot2Time]
                     : robot2Path[length2 - 1];

        printf("%-10d %-15d %-15d\n",
               t, pos1, pos2);
    }

    printf("\nSchedule completed without vertex or edge conflicts.\n");
    printf("Time Complexity: O(L1 + L2)\n");
    printf("Auxiliary Space Complexity: O(1)\n");
}