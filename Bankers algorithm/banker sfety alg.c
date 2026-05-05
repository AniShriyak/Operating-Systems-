#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int Allocation[P][R], Max[P][R], Need[P][R];
    int Total[R], Available[R], Work[R];
    bool Finish[P];
    int SafeSequence[P];

    // Input Allocation matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Input Max matrix
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    // Input Total resources
    printf("\nEnter Total Resources:\n");
    for (int j = 0; j < R; j++) {
        scanf("%d", &Total[j]);
    }

    // Calculate Available = Total - sum of Allocation
    for (int j = 0; j < R; j++) {
        int sum = 0;
        for (int i = 0; i < P; i++) {
            sum += Allocation[i][j];
        }
        Available[j] = Total[j] - sum;
        Work[j] = Available[j];
    }

    // Calculate Need = Max - Allocation
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Initialize Finish array
    for (int i = 0; i < P; i++) {
        Finish[i] = false;
    }

    int count = 0;

    // Safety Algorithm
    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j])
                        break;
                }

                // If all needs satisfied
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        Work[k] += Allocation[i][k];
                    }

                    SafeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process could be allocated
        if (!found) {
            printf("\nSystem is in UNSAFE state (Deadlock possible)\n");
            return 0;
        }
    }

    // Safe state
    printf("\nSystem is in SAFE state\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", SafeSequence[i]);
    }

    printf("\n");

    return 0;
}
