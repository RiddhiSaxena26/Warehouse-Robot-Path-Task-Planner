#include <stdio.h>
#include "warehouse.h"

// ==========================================
// DISPLAY WAREHOUSE TASKS
// ==========================================

void displayTasks(Task tasks[], int n) {

    if (tasks == NULL || n <= 0) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n%-10s %-12s %-12s %-10s\n",
           "Task ID", "Pickup", "Delivery", "Priority");

    printf("------------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("%-10d %-12d %-12d %-10d\n",
               tasks[i].taskID,
               tasks[i].pickup,
               tasks[i].delivery,
               tasks[i].priority);
    }
}


// ==========================================
// MERGE TWO SORTED ARRAYS
// ==========================================

static void merge(Task tasks[], int left, int mid, int right) {

    Task temp[MAX_TASKS];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {

        // Higher priority comes first
        if (tasks[i].priority >= tasks[j].priority) {
            temp[k++] = tasks[i++];
        } else {
            temp[k++] = tasks[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = tasks[i++];
    }

    while (j <= right) {
        temp[k++] = tasks[j++];
    }

    for (int x = 0; x < k; x++) {
        tasks[left + x] = temp[x];
    }
}


// ==========================================
// MERGE SORT ALGORITHM
// ==========================================

void mergeSort(Task tasks[], int left, int right) {

    if (tasks == NULL || left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(tasks, left, mid);
    mergeSort(tasks, mid + 1, right);

    merge(tasks, left, mid, right);
}


// ==========================================
// DISPLAY MERGE SORT DETAILS
// ==========================================

void demonstrateMergeSort(Task tasks[], int taskCount) {

    if (tasks == NULL || taskCount <= 0 ||
        taskCount > MAX_TASKS) {

        printf("\nInvalid task list.\n");
        return;
    }

    printf("\n========================================\n");
    printf("       TASK PRIORITY MANAGEMENT\n");
    printf("========================================\n");

    printf("Algorithm Used: Merge Sort\n");
    printf("Technique: Divide and Conquer\n");
    printf("Sorting Order: Highest Priority First\n\n");

    printf("Tasks Before Sorting:\n");
    displayTasks(tasks, taskCount);

    // Perform Merge Sort
    mergeSort(tasks, 0, taskCount - 1);

    printf("\nTasks After Sorting:\n");
    displayTasks(tasks, taskCount);

    printf("\nTime Complexity: O(n log n)\n");
    printf("Auxiliary Space Complexity: O(n)\n");

    printf("========================================\n");
}