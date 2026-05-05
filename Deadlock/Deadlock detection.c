#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX];
    int finish[MAX];
    int i, j, k;

    printf("===== Deadlock Detection Algorithm =====\n");

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize finish array
    for(i = 0; i < n; i++) {
        int hasAllocation = 0;
        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                hasAllocation = 1;
                break;
            }
        }
        if(hasAllocation == 0)
            finish[i] = 1;
        else
            finish[i] = 0;
    }

    // Deadlock detection logic
    int found;
    do {
        found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {

                // Check if request can be satisfied
                for(j = 0; j < m; j++) {
                    if(request[i][j] > avail[j])
                        break;
                }

                // If all requests can be satisfied
                if(j == m) {
                    // Release resources
                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;

                    printf("\nProcess P%d has completed, resources released.\n", i);
                }
            }
        }

    } while(found);

    // Check for deadlock
    int deadlock = 0;

    printf("\n===== Result =====\n");
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            printf("Process P%d is in DEADLOCK\n", i);
            deadlock = 1;
        }
    }

    if(deadlock == 0) {
        printf("No deadlock detected. System is safe.\n");
    }

    return 0;
}
