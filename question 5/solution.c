#include <stdio.h>
#include <stdlib.h>

// Structure to represent an interval
typedef struct {
    int start;
    int end;
} Interval;

// Utility function to return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Comparator function to sort intervals by start time
int compareIntervals(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;
    return i1->start - i2->start;
}

// Function to merge overlapping intervals in O(n log n) time
void mergeIntervals(Interval intervals[], int n) {
    if (n <= 0) return;

    // Step 1: Sort intervals based on start time in O(n log n)
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    // Array to store merged intervals
    Interval merged[n];
    int index = 0;

    // Start with the first interval
    merged[0] = intervals[0];

    // Step 2: Merge overlapping intervals in O(n)
    for (int i = 1; i < n; i++) {
        // If current interval overlaps with the previous one
        if (intervals[i].start <= merged[index].end) {
            merged[index].end = max(merged[index].end, intervals[i].end);
        } else {
            // No overlap, move to the next merged slot
            index++;
            merged[index] = intervals[i];
        }
    }

    // Print the merged intervals
    printf("Merged Intervals: {");
    for (int i = 0; i <= index; i++) {
        printf("(%d, %d)", merged[i].start, merged[i].end);
        if (i < index) printf(", ");
    }
    printf("}\n");
}

int main() {
    // Input set of intervals I = {(1, 3), (2, 6), (8, 10), (7, 18)}
    Interval I[] = {{1, 3}, {2, 6}, {8, 10}, {7, 18}};
    int n = sizeof(I) / sizeof(I[0]);

    printf("Original Intervals: {");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)", I[i].start, I[i].end);
        if (i < n - 1) printf(", ");
    }
    printf("}\n\n");

    mergeIntervals(I, n);

    return 0;
}