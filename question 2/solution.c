#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Helper comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Binary search implementation
bool binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return true;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

// Function to find pair with target sum x
bool findPairSum(int S1[], int S2[], int n, int x) {
    // Step 1: Sort S2 in O(n log n)
    qsort(S2, n, sizeof(int), compare);

    // Step 2: Iterate S1 and binary search (x - S1[i]) in S2
    for (int i = 0; i < n; i++) {
        int target = x - S1[i];
        if (binarySearch(S2, n, target)) {
            printf("Pair found: (%d from S1) + (%d from S2) = %d\n", S1[i], target, x);
            return true;
        }
    }
    return false;
}

int main() {
    int n = 5;
    int S1[] = {10, 3, 5, 2, 8};
    int S2[] = {4, 15, 1, 7, 9};
    int x = 12;

    printf("Set 1 (S1): ");
    for (int i = 0; i < n; i++) printf("%d ", S1[i]);
    printf("\nSet 2 (S2): ");
    for (int i = 0; i < n; i++) printf("%d ", S2[i]);
    printf("\nTarget x: %d\n\n", x);

    if (!findPairSum(S1, S2, n, x)) {
        printf("No pair found that adds up to %d\n", x);
    }

    return 0;
}
