#include <stdio.h>
#include "warehouse.h"

#define INITIAL_TASKS 5
#define INITIAL_ROBOTS 3

// Clear invalid input from terminal
void clearInputBuffer() {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// Read an integer safely
int readInteger(const char* message) {
    int value;

    while (1) {
        printf("%s", message);

        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            return value;
        }

        if (feof(stdin)) {
            return -1;
        }

        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
    }
}

// Display main menu
void displayMenu() {

    printf("\n==================================================\n");
    printf("       WAREHOUSE ROBOT PATH & TASK PLANNER\n");
    printf("==================================================\n");

    printf("1.  Display Warehouse Map\n");
    printf("2.  Explore Warehouse Using BFS\n");
    printf("3.  Explore Warehouse Using DFS\n");
    printf("4.  Find Shortest Path (Dijkstra)\n");
    printf("5.  Display Warehouse Tasks\n");
    printf("6.  Sort Tasks by Priority (Merge Sort)\n");
    printf("7.  Display Robot Status\n");
    printf("8.  Assign Tasks to Robots (Greedy)\n");
    printf("9.  Compare Task Optimization Algorithms\n");
    printf("10. Block a Warehouse Path\n");
    printf("11. Unblock a Warehouse Path\n");
    printf("12. Detect Robot Collisions\n");
    printf("13. Demonstrate Robot Scheduling\n");
    printf("14. Find Shortest Path (Bellman-Ford)\n");
    printf("15. Compare Shortest Path Algorithms\n");
    printf("0.  Exit\n");

    printf("==================================================\n");
}

int main() {

    // Create warehouse graph
    Graph* warehouse = createGraph(6);

    if (warehouse == NULL) {
        return 1;
    }

    // Warehouse connections
    addEdge(warehouse, 0, 1, 4);
    addEdge(warehouse, 0, 2, 2);
    addEdge(warehouse, 1, 3, 5);
    addEdge(warehouse, 2, 3, 3);
    addEdge(warehouse, 2, 4, 6);
    addEdge(warehouse, 3, 5, 2);
    addEdge(warehouse, 4, 5, 4);

    // Warehouse tasks
    Task tasks[INITIAL_TASKS] = {
        {101, 2, 5, 3},
        {102, 1, 4, 1},
        {103, 3, 0, 5},
        {104, 4, 2, 2},
        {105, 5, 1, 4}
    };

    // Warehouse robots
    Robot robots[INITIAL_ROBOTS] = {
        {1, 0, 0, 0},
        {2, 3, 0, 0},
        {3, 5, 0, 0}
    };

    // Tasks for optimization comparison
    Task optimizationTasks[] = {
        {101, 2, 5, 3},
        {102, 1, 4, 1},
        {103, 3, 0, 5}
    };

    int optimizationCount =
        sizeof(optimizationTasks) / sizeof(optimizationTasks[0]);

    // Example robot routes
    int robot1Path[] = {0, 2, 3, 5};
    int robot2Path[] = {5, 3, 2, 0};

    int length1 = sizeof(robot1Path) / sizeof(robot1Path[0]);
    int length2 = sizeof(robot2Path) / sizeof(robot2Path[0]);

    int choice;
    int start;
    int destination;
    int source;
    int target;

    // Prevent assigning the same tasks repeatedly
    int tasksAssigned = 0;

    do {

        displayMenu();

        choice = readInteger("Enter your choice: ");

        switch (choice) {

            case 1:
                displayGraph(warehouse);
                break;

            case 2:
                start = readInteger("Enter starting location: ");
                BFS(warehouse, start);
                break;

            case 3:
                start = readInteger("Enter starting location: ");
                DFS(warehouse, start);
                break;

            case 4:
                start = readInteger("Enter starting location: ");
                destination = readInteger("Enter destination: ");

                dijkstra(warehouse, start, destination);
                break;

            case 5:
                printf("\n========== WAREHOUSE TASKS ==========\n");
                displayTasks(tasks, INITIAL_TASKS);
                break;

            case 6:
                demonstrateMergeSort(tasks, INITIAL_TASKS);
                break;

            case 7:
                displayRobots(robots, INITIAL_ROBOTS);
                break;

            case 8:
                if (tasksAssigned) {
                    printf("\nTasks have already been assigned.\n");
                    break;
                }

                // Ensure priority order before assignment
                mergeSort(tasks, 0, INITIAL_TASKS - 1);

                assignTasks(
                    warehouse,
                    robots,
                    INITIAL_ROBOTS,
                    tasks,
                    INITIAL_TASKS
                );

                tasksAssigned = 1;

                printf("\nUpdated robot status:\n");
                displayRobots(robots, INITIAL_ROBOTS);
                break;

            case 9:
                greedyTaskOptimization(
                    warehouse,
                    optimizationTasks,
                    optimizationCount,
                    0
                );

                bruteForceTaskOptimization(
                    warehouse,
                    optimizationTasks,
                    optimizationCount,
                    0
                );
                break;

            case 10:
                source = readInteger("Enter first location: ");
                target = readInteger("Enter second location: ");

                blockPath(warehouse, source, target);
                break;

            case 11:
                source = readInteger("Enter first location: ");
                target = readInteger("Enter second location: ");

                unblockPath(warehouse, source, target);
                break;

            case 12:
                detectCollisions(
                    robot1Path,
                    length1,
                    robot2Path,
                    length2
                );
                break;

            case 13:
                scheduleRobots(
                    robot1Path,
                    length1,
                    robot2Path,
                    length2
                );
                break;

            case 14:
                start = readInteger("Enter starting location: ");
                destination = readInteger("Enter destination: ");

                bellmanFord(warehouse, start, destination);
                break;

            case 15:
                start = readInteger("Enter starting location: ");
                destination = readInteger("Enter destination: ");

                compareShortestPathAlgorithms(
                    warehouse,
                    start,
                    destination
                );
                break;

            case 0:
                printf("\nExiting Warehouse Robot Planner...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    // Release allocated graph memory
    freeGraph(warehouse);

    return 0;
}