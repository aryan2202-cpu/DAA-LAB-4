#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Helper comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Recursive helper to fix k-2 elements and use two pointers for the last 2
bool findKSumRecursive(int arr[], int n, int target, int k, int start, int result[], int depth) {
    // Base Case: When k = 2, use Two-Pointer Search in O(n)
    if (k == 2) {
        int left = start, right = n - 1;
        while (left < right) {
            int current_sum = arr[left] + arr[right];
            if (current_sum == target) {
                result[depth] = arr[left];
                result[depth + 1] = arr[right];
                return true;
            } else if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return false;
    }

    // Fix one element and recurse for (k - 1) elements
    for (int i = start; i <= n - k; i++) {
        result[depth] = arr[i];
        if (findKSumRecursive(arr, n, target - arr[i], k - 1, i + 1, result, depth + 1)) {
            return true;
        }
    }

    return false;
}

bool hasKSum(int arr[], int n, int T, int k) {
    if (n < k) return false;

    // Step 1: Sort the array in O(n log n)
    qsort(arr, n, sizeof(int), compare);

    int *result = (int *)malloc(k * sizeof(int));
    bool found = findKSumRecursive(arr, n, T, k, 0, result, 0);

    if (found) {
        printf("Found %d elements that sum to %d: ", k, T);
        for (int i = 0; i < k; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    free(result);
    return found;
}

int main() {
    int S[] = {1, 4, 45, 6, 10, 8, 12};
    int n = sizeof(S) / sizeof(S[0]);
    int T = 22;
    int k = 3;

    printf("Array S: ");
    for (int i = 0; i < n; i++) printf("%d ", S[i]);
    printf("\nTarget T = %d, k = %d\n\n", T, k);

    if (!hasKSum(S, n, T, k)) {
        printf("No %d elements sum to %d\n", k, T);
    }

    return 0;
}