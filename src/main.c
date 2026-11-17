#include <stdio.h>
#include "warehouse.h"

int main() {

    Graph* warehouse = createGraph(6);

    if (warehouse == NULL) {
        return 1;
    }

    // Warehouse paths and distances
    addEdge(warehouse, 0, 1, 4);
    addEdge(warehouse, 0, 2, 2);
    addEdge(warehouse, 1, 3, 5);
    addEdge(warehouse, 2, 3, 3);
    addEdge(warehouse, 2, 4, 6);
    addEdge(warehouse, 3, 5, 2);
    addEdge(warehouse, 4, 5, 4);

    displayGraph(warehouse);

    freeGraph(warehouse);

    return 0;
}