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
        length1 > MAX_TIME || length2 > MAX_TIME) {

        printf("\nInvalid robot paths.\n");
        return;
    }

    printf("\n========== ROBOT SCHEDULING ==========\n");

    printf("\nRobot 1 follows its original route.\n");
    printf("Robot 2 waits until Robot 1 finishes.\n");

    int totalTime = (length1 - 1) + (length2 - 1);

    printf("\n%-10s %-15s %-15s\n",
           "Time", "Robot 1", "Robot 2");

    printf("------------------------------------------\n");

    for (int t = 0; t <= totalTime; t++) {

        int pos1 = getPosition(robot1Path, length1, t);

        int robot2Time = t - (length1 - 1);

        int pos2;

        if (robot2Time < 0) {
            pos2 = robot2Path[0];
        } else {
            pos2 = getPosition(
                robot2Path,
                length2,
                robot2Time
            );
        }

        printf("%-10d %-15d %-15d\n",
               t, pos1, pos2);
    }

    printf("\nScheduling completed.\n");
}