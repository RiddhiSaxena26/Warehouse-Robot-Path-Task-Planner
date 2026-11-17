#include <stdio.h>
#include "warehouse.h"

// Display all warehouse tasks
void displayTasks(Task tasks[], int n) {

    printf("\n%-10s %-12s %-12s %-10s\n",
           "Task ID", "Pickup", "Delivery", "Priority");

    printf("-----------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        printf("%-10d %-12d %-12d %-10d\n",
               tasks[i].taskID,
               tasks[i].pickup,
               tasks[i].delivery,
               tasks[i].priority);
    }
}

// Merge two sorted parts
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

    // Copy remaining left-side tasks
    while (i <= mid) {
        temp[k++] = tasks[i++];
    }

    // Copy remaining right-side tasks
    while (j <= right) {
        temp[k++] = tasks[j++];
    }

    // Copy sorted tasks back
    for (int x = 0; x < k; x++) {
        tasks[left + x] = temp[x];
    }
}

// Merge Sort algorithm
void mergeSort(Task tasks[], int left, int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(tasks, left, mid);
    mergeSort(tasks, mid + 1, right);

    merge(tasks, left, mid, right);
}